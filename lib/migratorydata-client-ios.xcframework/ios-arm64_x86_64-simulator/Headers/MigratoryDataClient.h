/*
 * Copyright (c) 2007-2020 Migratory Data Systems (http://migratorydata.com)
 * ALL RIGHTS RESERVED. Use is subject to license terms.
 */
#import <Foundation/Foundation.h>
#import "MigratoryDataGlobals.h"
#import "MigratoryDataListener.h"

@class MigratoryDataListener;
@class MigratoryPushClientImpl;

/**
 * This class implements all the necessary operations for connecting to a cluster of one or more MigratoryData servers,
 * subscribing to one or more subjects, getting real-time messages for the subscribed subjects, and publishing messages.
 */
@interface MigratoryDataClient : NSObject {
	@private
	MigratoryPushClientImpl *_pushClientImpl;
}

/**
 * Create a MigratoryDataClient object.
 */
- (id) init;

/**
 * Use this method to connect this client to one of the MigratoryData servers you specified with
 * \link MigratoryDataClient.setServers() \endlink, and subscribe to the subjects you specified with
 * \link MigratoryDataClient.subscribe() \endlink, if any.
 */
- (void) connect;

/**
 * Attach a listener for handling the received real-time messages as well as the status notifications.
 *
 * \param listener   an implementation of the \link MigratoryDataListener \endlink interface
 */
- (void) setListener: (NSObject<MigratoryDataListener> *)listener;

/**
 * Specify the log level used for application logging.
 *
 * \param logLevel   a log level from enum \link MigratoryDataLogLevel \endlink
 */
- (void) setLogLevel: (MigratoryDataLogLevel)logLevel;


/**
 * Specify a cluster of one or more MigratoryData servers to which the client will connect to.
 *
 * For example, to connect to a cluster formed of two MigratoryData servers installed at the addresses
 * \c p1.example.com and \c p2.example.com, and configured to accept clients on the standard HTTP port \c 80, the
 * following code can be used:
 *
 * ```js
 *    NSArray *servers = [NSArray arrayWithObjects:@"p1.example.com:80", @"p2.example.com:80"];
 *    [client setServers:servers];
 * ```
 *
 * To achieve load-balancing, the API connects the client to a MigratoryData server chosen randomly from the
 * \c servers list. In this way, the load is balanced among all the members of the cluster.
 *
 * Moreover, the API supports weighted load-balancing. This feature is especially useful if the MigratoryData
 * servers of the cluster are installed on machines with different capacities. You can assign to each member of the
 * cluster a \em weight ranging from \c 0 to \c 100. This weight assignment is a hint provided to the API to select
 * with a higher probability a MigratoryData server with a higher weight either initially when the client connects
 * to the cluster or later during a failover reconnection.
 *
 * Supposing the address \c p1.example.com corresponds to a machine that is twice more powerful than the machine
 * having the address \c p2.example.com, then you can assign to \c p1.example.com a weight \c 100 and to
 * \c p2.example.com a weight \c 50 by prefixing each address with the assigned weight as follows:
 *
 * ```js
 *    NSArray *servers = [NSArray arrayWithObjects:@"100 p1.example.com", @"50 p2.example.com"];
 *    [client setServers:servers];
 * ```
 *
 * The API assigns a default weight \c 100 to the addresses not prefixed with a specific weight.
 *
 * To achieve failover, if the connection between the client and a MigratoryData server is broken, then the API will
 * automatically detect the failure and will select another MigratoryData server from the \c servers list. If the
 * client fails to connect to the newly selected server, a status notification MigratoryDataClient.NOTIFY_SERVER_DOWN
 * will be triggered, unless this is modified using \link MigratoryDataClient.notifyAfterFailedConnectionAttempts() \endlink),
 * and a new MigratoryData server of the cluster will be selected again and again until the client will be able to connect to one of the MigratoryData servers of
 * the cluster. When successfully connected, the API will trigger
 * MigratoryDataClient.NOTIFY_SERVER_UP.
 *
 * Furthermore, if the Guaranteed Message Delivery feature is enabled for the MigratoryData cluster, then the messages
 * potentialy published for a subscribed subject during the failover period will be automatically recovered from
 * the cache of the MigratoryData server to which the client reconnects to and a status notification
 * \link MigratoryDataClient.NOTIFY_DATA_SYNC \endlink will be triggered for that subject.
 *
 * If, for example, the failover period is abnormally long, and the client is not able to recover all the messages
 * made available during the failover period for one of its subscribed subjects, then the API will retrieve only the
 * most recent retained message available for that subject and will trigger a MigratoryDataClient.NOTIFY_DATA_RESYNC
 * status notification for that subject, the client behaving as a new client.
 *
 * For a complete discussion about load balancing, failover, and guaranteed message delivery features see the
 * <em>Architecture Guide</em>.
 *
 * \param servers   an array of strings where each string represents the network address (IP address or DNS domain
 *                  name and its corresponding port) of a MigratoryData server, optionally prefixed by a weight
 *                  ranging from \c 0 to \c 100; if the weight prefix is not provided to an address, then the API will
 *                  automatically assign to that address a default weight \c 100
 */
- (void) setServers: (NSArray *)servers;

/**
 *  Subscribe to one or more subjects.
 *
 *  The MigratoryData subjects are strings having a particular syntax. See the Chapter "Concepts" of the Architecture
 *  Guide to learn about the syntax of the subjects.
 *
 *  As an example, supposing messages are market data updates having as subjects stock names. Then, to subscribe for
 *  the messages having as subjects \c /stocks/NYSE/IBM and \c /stocks/Nasdaq/MSFT use:
 *
 * ```js
 * NSMutableArray *subjects = [NSMutableArray new];
 * [subjects addObject:@"/stocks/NYSE/IBM"];
 * [subjects addObject:@"/stocks/Nasdaq/MSFT"];
 * [client subscribe:subjects];
 * ```
 *
 *
 * \param subjects   An array of strings representing subjects.
 */
- (void) subscribe: (NSArray *)subjects;

/**
 *  Subscribe to one or more subjects after getting historical messages for those subjects
 *
 *  The MigratoryData subjects are strings having a particular syntax. See the Chapter "Concepts" of the Architecture
 *  Guide to learn about the syntax of the subjects.
 *
 *  Attempt to get the number of historical messages as defined by the argument \c numberOfHistoricalMessages,
 *  for each subject in the argument \c subjects, then subscribe for real-time messages having as
 *  subjects the strings provided in the \c subjects parameter.
 *
 *  When Guaranteed Message Delivery is enabled, each MigratoryData server in the cluster maintains an in-memory
 *  cache with historical messages for each subject. The cache of each subject is available in all servers of the cluster.
 *  The maximum number of messages held in cache is defined by the parameter \c MaxCachedMessagesPerSubject of the MigratoryData
 *  server which defaults to 1,000 messages. The historical messages are continuously removed from the cache, but it is guaranteed that
 *  they are available in the cache at least the number of seconds defined by the parameter \c CacheExpireTime which
 *  defaults to 180 seconds.
 *
 *  If the value of \c numberOfHistoricalMessages is higher than the number of historical messages available in the cache, then
 *  the client will receive only the messages available in the cache. As a consequence, if you use a value higher than the value of the
 *  parameter \c MaxCachedMessagesPerSubject of the MigratoryData server (which defaults to 1000), then you will get the entire
 *  cache before subscribing for real-time messages for the subjects specified with the API call.
 *
 *  If the value of \c numberOfHistoricalMessages is \c 0, then no historical messages have to be retrieved from the
 *  cache and, in this case, this API method is equivalent to the API method  \link MigratoryDataClient.subscribe() \endlink.
 *
 * \param subjects An array of strings representing subjects.
 * \param numberOfHistoricalMessages   the number of historical messages to be retrieved from the cache of the server
 */
- (void) subscribeWithHistory: (NSArray *)subjects history:(int)history;

/**
 * Unsubscribe from one or more subjects.
 *
 * \param subjects   subjects to unsubscribe
 */
- (void) unsubscribe: (NSArray *)subjects;

/**
 * Configure whether to use SSL/TLS encryption when connecting to a MigratoryData server.
 *
 * When using encryption you should connect to the ports of the MigratoryData server that are configured with the
 * parameter \c ListenEncrypted to listen for encrypted connections.
 *
 * \param encrypted   indicate whether or not to use an encrypted SSL/TLS connection to communicate with the server
 */
- (void) setEncryption: (BOOL)encryption;

/**
 * Assign an entitlement token to the client or update its entitlement token.
 *
 * To define which users of your application have access to which subjects, you will first have to configure the
 * parameter ```Entitlement```, see the <em>Configuration Guide</em>. If you set this parameter on
 * \c Custom, then you can use the <em>MigratoryData Authorization Extension</em> to build an extension plugin
 * for the MigratoryData server to allow or deny certain users to subscribe to or publish on certain subjects.
 *
 * \param token  a string representing an entitlement token
 */
- (void) setEntitlementToken: (NSString *)token;

/**
 * Return the list of subscribed subjects.
 *
 * \return The list of strings representing the subscribed subjects.
 */
- (NSArray *) getSubjects;

/**
 *  Define the number of failed attempts to connect to one or more MigratoryData servers before triggering a status
 *  notification MigratoryDataClient.NOTIFY_SERVER_DOWN.
 *
 * \param retries   the number of the failed attempts to connect to one or more MigratoryData servers before
 *                  triggering a status notification MigratoryDataClient.NOTIFY_SERVER_DOWN; the default is \c 1
 */
- (void) notifyAfterFailedConnectionAttempts: (int)n;

/**
 *  Publish a message.
 *
 *  If the message includes a closure data, then a status notification will be provided via
 *  \link MigratoryDataListener.onStatus() \endlink to inform whether the message publication
 *  has been successful or failed.
 *
 * \param message A MigratoryDataMessage message
 */
- (void) publish: (MigratoryDataMessage *)message;

/**
 * Pause the API operation.
 *
 * If the application built with this API library enters into background, then it is 
 * recommended to use this API call. It will disconnect the user from the MigratoryData 
 * sever but will preserve the user's context (including the cluster definition and 
 * subscribed subjects) in order to reconnect to the cluster later when the API method 
 * \link MigratoryDataClient.resume \endlink is called.
 *
 * Moreover, if the cluster is configured with guaranteed message delivery, then when the user
 * will reconnect to the cluster using \link MigratoryDataClient.resume \endlink, it will get
 * all messages published since the \link MigratoryDataClient.pause \endlink method was called,
 * provided however that the duration between the time when \link MigratoryDataClient.pause \endlink
 * method was called and the \link MigratoryDataClient.resume \endlink method was called is
 * less than the value defined by the parameter ```CacheExpireTime``` of the
 * MigratoryData server (see details about this parameter in <em>MigratoryData Configuration Guide</em>.
 */
- (void) pause;

/**
 * Resume the API operation.
 *
 * If the application was paused with the \link MigratoryDataClient.pause \endlink method, then
 * this API call will attempt to reconnect the user to the cluster. Also, if guaranteed message delivery
 * is enabled, this method also retrieves all messages published since the 
 * \link MigratoryDataClient.pause \endlink has been called provided that the duration between the
 * time when \link MigratoryDataClient.pause \endlink method was called and the
 * \link MigratoryDataClient.resume \endlink method was called is smaller than the value
 * defined by the parameter  ```CacheExpireTime```.
 *
 * This method will be typically used when the application switches to foreground.
 */
- (void) resume;

/**
 * Disconnect from the connected MigratoryData server and dispose the resources used by the connection.
 *
 * This method should be called when the connection is no longer necessary.
 */
- (void) disconnect;

/**
 * Define the maximum number of retries for the Quick Reconnect fail-over phase.
 *
 * See \link MigratoryDataClient.setQuickReconnectInitialDelay() \endlink to learn about the Quick Reconnect phase.
 *
 * \param retries   the maximum number of quick reconnect retries; the default is \c 3
 */
- (void) setQuickReconnectMaxRetries:(int) retries;

/**
 * Define the number of seconds to wait before attempting to reconnect to the cluster after a connection failure is detected.
 *
 * <h5>Connection Failure Detection</h5>
 *
 * Connection failure is detected immediately for almost all users. For a few users which are subject to temporary, atypical network conditions,
 * connection failure is detected after 30-40 seconds.
 *
 * <h5>Reconnection Phases and Policies</h5>
 *
 * When a connection failure is detected, the API will attempt to reconnect to the servers of the MigratoryData cluster as follows:
 * First, it will attempt to reconnect up to a number of times as defined by \link MigratoryDataClient.setQuickReconnectMaxRetries() \endlink
 * using small delays between retries (Quick Reconnection Phase). If the connection cannot be established after the Quick Reconnection Phase,
 * then the API will attempt to reconnect less frequently according to the policy defined by \link MigratoryDataClient.setReconnectPolicy() \endlink.
 *
 * The delays between retries are computed according to the following algorithm where the values of the variables involved are defined by the API methods having substantially the same names:
 *
 * ```
 *    Quick Reconnect Phase (retries <= quickReconnectMaxRetries)
 *    -----------------------------------------------------------
 *
 *       (retries starts with 1 and increment by 1 at each quick reconnect)
 *
 *       reconnectDelay = quickReconnectInitialDelay * retries - random(0, quickReconnectInitialDelay)
 *
 *    After Quick Reconnect Phase (retries > quickReconnectMaxRetries)
 *    ----------------------------------------------------------------
 *
 *       (reset retries to start with 1 and increment by 1 at each reconnect)
 *
 *       If reconnectPolicy is CONSTANT_WINDOW_BACKOFF, then
 *
 *          reconnectDelay = reconnectTimeInterval
 *
 *       else if reconnectPolicy is TRUNCATED_EXPONENTIAL_BACKOFF, then
 *
 *          reconnectDelay = min(reconnectTimeInterval * (2 ^ retries) - random(0, reconnectTimeInterval * retries), reconnectMaxDelay)
 * ```
 *
 * For a few users which are subject to temporary, atypical network conditions, if <code>reconnectDelay</code> computed
 * with the algorithm above is less than 10 seconds, then it is rounded to 10 seconds.
 *
 * \param seconds The number of seconds to wait before attempting to reconnect to the cluster; default value is <code>5</code> seconds.
 */
- (void) setQuickReconnectInitialDelay:(int) seconds;

/**
 * Define the reconnect policy to be used after the Quick Reconnect phase.
 *
 * See \link MigratoryDataClient.setQuickReconnectInitialDelay() \endlink to learn about the Quick Reconnect phase
 * and the reconnect schedule for the policy defined by this method.
 *
 * \param  policy   the reconnect policy to be used after the Quick Reconnect phase; the possible values are:
 *                  \link CONSTANT_WINDOW_BACKOFF \endlink and
 *                  \link TRUNCATED_EXPONENTIAL_BACKOFF \endlink; the default value is
 *                    \link TRUNCATED_EXPONENTIAL_BACKOFF \endlink;
 */
- (void) setReconnectPolicy:(NSString* ) policy;

/**
 * Define the time interval used for the reconnect schedule after the Quick Reconnect phase.
 *
 * See \link MigratoryDataClient.setQuickReconnectInitialDelay() \endlink to learn about the Quick Reconnect phase
 * and the reconnect schedule for the policy defined by this method.
 *
 * \param seconds A time interval expressed in seconds used for reconnect schedule; default is <code>20</code> seconds.
 */
- (void) setReconnectTimeInterval:(int) seconds;

/**
 * Define the maximum reconnect delay for the TRUNCATED_EXPONENTIAL_BACKOFF policy.
 *
 * See \link MigratoryDataClient.setQuickReconnectInitialDelay() \endlink to learn how the value defined by this
 * method is used.
 *
 * \param seconds The maximum reconnect delay when the policy \link TRUNCATED_EXPONENTIAL_BACKOFF \endlink is used; default value is 360 seconds.
 */
- (void) setReconnectMaxDelay:(int) seconds;

/**
 * Assigns an external token to enable client communication via external services while the client is offline.
 *
 * Presuming a client goes offline and disconnects from the MigratoryData cluster. Then plugins within the MigratoryData
 * server, leveraging MigratoryData's Presence API, can utilize this external token to communicate with the offline
 * client, via external services like push notifications or email.
 *
 * For instance, consider a plugin designed for Firebase Cloud Messaging (FCM), which requires an FCM token to send
 * push notifications to a client via FCM. Through this method, the client can provide the necessary FCM token to the plugin.
 *
 * Similarly, consider a plugin designed for email services. To send emails to clients when they're offline, the
 * plugin requires their email addresses. Clients can provide their email addresses using this method.
 *
 * @param externalToken   a token (e.g. FCM token, email address, ...)
 */

- (void) setExternalToken: (NSString *)externalToken;

/**
 * Define the transport type used by the client to communicate with the MigratoryData cluster.
 *
 * \param  type   the possible values are:
 *                TRANSPORT_HTTP and
 *                TRANSPORT_WEBSOCKET;
 *                the default transport used by the API is TRANSPORT_WEBSOCKET
 */
- (void) setTransport: (NSString *)transport;

/**
  * This method allows for the inclusion of custom HTTP headers. In the case of the WebSocket transport, the added headers
 * are transmitted during the handshake. For the HTTP transport, the added headers are sent with every client request.
 *
 * This functionality is particularly useful when an authentication solution is in place between the client and the MigratoryData server,
 * which requires an HTTP header containing an authentication token.
 *
 * \remark This method should be used only for Node.js applications.
 *
 * \param header header name
 * \param value header value
 */
- (void) setHttpHeader: (NSString *)name value:(NSString *)value;


@end
