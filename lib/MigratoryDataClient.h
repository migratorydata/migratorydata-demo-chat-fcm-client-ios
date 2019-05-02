/*
 * Copyright (c) 2007-2014 Migratory Data Systems (http://migratorydata.com)
 * ALL RIGHTS RESERVED. Use is subject to license terms.
 */
#import <Foundation/Foundation.h>
#import "MigratoryDataGlobals.h"
#import "MigratoryDataListener.h"

@class MigratoryDataListener;
@class MigratoryPushClientImpl;

/** \file MigratoryDataClient.h
 * 
 * \brief Include the declaration of the \link MigratoryDataClient \endlink class.
 */

/** \mainpage Developer's Guide
*
* This guide includes the following sections:
* 
* \li \ref overview
* \li \ref howto
* \li \ref examples
* 
* \section overview Overview
*
* This application programming interface (API) contains all the necessary operations for
* connecting to a cluster of one or more MigratoryData servers, subscribing to subjects,
* getting real-time messages for the subscribed subjects, and
* publishing real-time messages.
*
* Before reading this manual, it is recommended to read <em>MigratoryData Architecture Guide</em>
* (<a target="_blank" href="http://migratorydata.com/documentation/pdf/Architecture.pdf">PDF</a>,
* <a target="_blank" href="http://migratorydata.com/documentation/html/Architecture/Architecture.html">HTML</a>).
*
* \section howto Creating iOS clients for MigratoryData Server
* 
* A typical API usage is as follows:
*
* \subsection step1 Step 1 - Include the library.
* 
* Include the headers of the API located in the folder \c lib of this API package. 
* 
* Add the \c lib folder to the <em>Include Directories</em> of your iOS application. 
* 
* The API library is available in the folder \c lib of this API package. Add the \c lib folder to the <em>Library Directories</em> of
* your iOS application. Also, add the API library itself to the list of <em>Library Dependencies</em> of your iOS application. 
* 
* \subsection step2 Step 2 - Define the listener class to get the real-time messages and status notifications.
* 
* The listener should implement the \link MigratoryDataListener \endlink interface.
*
* Use the API call \link MigratoryDataClient::setListener: \endlink to attach your listener implementation.
*
* \subsection step3 Step 3 - Specify the list of MigratoryData servers where to connect to.
* 
* Use the API method \link MigratoryDataClient::setServers: \endlink to specify one or more MigratoryData servers to which your 
* iOS client will connect to. In fact, the iOS client will connect to only one of the MigratoryData servers in 
* this list. But, defining two or more MigratoryData servers is recommended to achieve fail-over (and horizontal scalling / load balancing). 
* Supposing the MigratoryData server - to which the iOS client connected - goes down, then the API will automatically 
* reconnect that client to another MigratoryData server in the list.   
* 
* \subsection step4 Step 4 Subscribe to subjects and publish messages
*
* Use the API method \link MigratoryDataClient::subscribe: \endlink to subscribe to subjects and
* use the API method \link MigratoryDataClient::publish: \endlink to publish messages.
*
* \subsection step5 Step 5 - Handle the real-time messages and status notifications.
* 
* Handle the messages received for the subscribed subjects as well as the status notifications in your listener implementation defined at Step 2 above.
*
* \section examples Examples
*
* Examples built with this API are available in the folder \c examples of this API package; start with the README file which 
* explains how to compile and run them. 
* \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n
*/

/**
 * \brief This class implements all the necessary operations for connecting to a cluster of one or more MigratoryData servers,
 * subscribing to subjects, getting real-time messages for the subscribed subjects, and publishing real-time messages.
 */
@interface MigratoryDataClient : NSObject {
	@private
	MigratoryPushClientImpl *_pushClientImpl;
}

/**
 * \brief Create a MigratoryDataClient object.
 */
- (id) init;

/**
 * \brief Configure the logging level.
 *
 * It is advisable to configure this first if you want to log as much as possible. The default log level is \link LogType.LOG_INFO \endlink.
 *
 * @param logLevel
 *            The logging verbosity (\link LogType.LOG_ERROR \endlink, \link LogType.LOG_INFO \endlink, \link LogType.LOG_DEBUG \endlink or \link LogType.LOG_TRACE \endlink ); by 
 *            default \link LogType.LOG_INFO \endlink is configured.
 */
- (void) setLogType: (LogType)logLevel;

/**
 * \brief Attach a MigratoryDataListener for handling real-time messages and status notifications.
 *
 * \param listener
 * 			An instance of a class which implements the \link MigratoryDataListener \endlink interface
 */
- (void) setListener: (NSObject<MigratoryDataListener> *)listener;

/**
 * \brief Specify a cluster of one or more MigratoryData servers to which the client will connect to.
 *
 * If you specify two or more MigratoryData servers, then all these MigratoryData servers should provide the same level of data redundancy, by making
 * available for subscription the same set of subjects. This is required for achieving (weighted) load balancing, failover, and
 * guaranteed message delivery of the system. In this way, the MigratoryData servers of the \c servers list form a \em cluster.
 *
 * For example, to connect to a cluster formed of two MigratoryData servers installed at the addresses \c p1.example.com and \c p2.example.com,
 * and configured to accept clients on the standard HTTP port \c 80, the following code can be used:
 *
 * <pre>
 * NSArray *servers = [NSArray arrayWithObjects:@"p1.example.com:80", @"p2.example.com:80"];
 * [client setServers:servers];
 * </pre>
 * 
 * To achieve load-balancing, the API connects the client to a MigratoryData server chosen randomly from the \c servers list. In this way,
 * the load is balanced among all the members of the cluster.
 *
 * <blockquote>
 * <small>
 * Moreover, the API supports weighted load-balancing. This feature is especially useful if the MigratoryData servers in the cluster are installed on
 * machines with different capacities. You can assign to each member of the cluster a \em weight ranging from \c 0 to \c 100.
 * This weight assignment is a hint provided to the API to select with a higher probability a MigratoryData server with a higher weight
 * either initially when the client connects to the cluster or later during a failover reconnection.
 *
 * Supposing the address \c p1.example.com corresponds to a machine that is twice more powerful than the machine having the
 * address \c p2.example.com, then you can assign to \c p1.example.com a weight \c 100 and to \c p2.example.com a weight
 * \c 50 by prefixing each address with the assigned weight as follows:
 *
 * <pre>
 * NSArray *servers = [NSArray arrayWithObjects:@"100 p1.example.com", @"50 p2.example.com"];
 * [client setServers:servers];
 * </pre>
 * 
 * The API assigns a default weight \c 100 to the addresses not prefixed with a specific weight.
 * </small>
 * </blockquote>
 *
 * To achieve failover, if the connection between the client and a MigratoryData server is broken, then the API will automatically
 * detect the failure and will select another MigratoryData server from the \c servers list. If the client fails to connect to the
 * new selected server, a status notification NOTIFY_SERVER_DOWN will be triggered (unless you modify the number of failed
 * attempts with \link MigratoryDataClient::setServersDownBeforeNotify: \endlink), and a new MigratoryData server in the cluster will be selected again
 * and again until the client will be able to connect to one of the MigratoryData servers in the cluster. When successfully connected,
 * the API will trigger a status notification \link NOTIFY_SERVER_UP \endlink.
 *
 * <blockquote>
 * <small>
 * Furthermore, if guaranteed message delivery is enabled, then the potential messages published for a subscribed subject during the failover period,
 * will be automatically retrieved from the cache of the MigratoryData server to which the client reconnects to and a status notification
 * \link NOTIFY_DATA_SYNC \endlink will be triggered for that subject.
 *
 * If, for example, the failover period is abnormally long, and the client is not able to retrieve, after a failover reconnection, the messages
 * published during the failover period for one of its subscribed subjects, then the API will retrieve only the most recent message available for
 * that subject and will trigger a \link NOTIFY_DATA_RESYNC \endlink status notification for that subject, the client
 * behaving as a new client which connects to the cluster at the moment of the failover reconnection.
 * </small>
 * </blockquote>
 *
 * For a complete discussion related to load balancing, failover, and guaranteed message delivery features see the <em>MigratoryData Architecture Guide</em>
 * (<a target="_blank" href="http://migratorydata.com/documentation/pdf/Architecture.pdf">PDF</a>,
 * <a target="_blank" href="http://migratorydata.com/documentation/html/Architecture/Architecture.html">HTML</a>).
 *
 * \param servers An array of strings where each string represents the network address (IP address or DNS domain name and its corresponding port)
 *                of a MigratoryData server, optionally prefixed by a weight ranging from \c 0 to \c 100. If the weight prefix is not provided to an
 *                address, then the API will automatically assign to that address a default weight \c 100.
 */
- (void) setServers: (NSArray *)servers;

/**
 * \brief Subscribe to one or more subjects.
 *
 *  Subscribe for real-time messages having as subjects the strings provided in the \c subjects parameter.
 *
 *  As an example, supposing messages are market data updates having as subjects stock names. Then, to subscribe for the
 *  messages having as subjects \c /stocks/NYSE/IBM and \c /stocks/Nasdaq/MSFT the following code will be used:
 *
 * <pre>
 * NSMutableArray *subjects = [NSMutableArray new];
 * [subjects addObject:@"/stocks/NYSE/IBM"];
 * [subjects addObject:@"/stocks/Nasdaq/MSFT"];
 * [client subscribe:subjects];
 * </pre>
 *  
 *  The subjects are strings having a particular syntax. See the Chapter "Concepts" in the <em>MigratoryData Architecture Guide</em>
 *  (<a target="_blank" href="http://migratorydata.com/documentation/pdf/Architecture.pdf">PDF</a>,
 *  <a target="_blank" href="http://migratorydata.com/documentation/html/Architecture/Architecture.html">HTML</a>)
 *  to learn about the syntax of the subjects.
 *
 * \param subjects An array of strings representing subjects.
 */
- (void) subscribe: (NSArray *)subjects;

/**
 * \brief Subscribe to one or more subjects with conflation.
 *
 *  Subscribe for real-time messages having as subjects the strings provided in the \c subjects parameter.
 *
 *  If the optional parameter \c conflationMillis is used, then for each subject in the \c subjects list given in argument, its messages will
 *  be aggregated in the MigratoryData server and published every \c conflationMillis milliseconds as aggregated data (containing only the latest
 *  value for that subject and its latest field values). The value of \c conflationMillis should be a multiple of \c 100 milliseconds,
 *  otherwise the MigratoryData server will round it to the nearest value multiple of \c 100 milliseconds (e.g. \c 76 will be rounded to \c 0,
 *  \c 130 will be rounded to \c 100, \c 789 will be rounded to \c 700, ...). If the value of \c conflationMillis is \c 0 (or is rounded to \c 0),
 *  then no conflation will apply, and data publication will be message-by-message with no message aggregation.
 *
 *  As an example, supposing the messages are market data updates having as subjects stock names. Then, to subscribe for the
 *  messages having as subjects \c /stocks/NYSE/IBM and \c /stocks/Nasdaq/MSFT using 1-second conflation the following code will be used:
 *
 * <pre>
 * NSMutableArray *subjects = [NSMutableArray new];
 * [subjects addObject:@"/stocks/NYSE/IBM"];
 * [subjects addObject:@"/stocks/Nasdaq/MSFT"];
 * [client subscribeWithConflation:subjects conflationTimeMillis:1000];
 * </pre>
 *  
 *  The subjects are strings having a particular particular syntax. See the Chapter "Concepts" in the <em>MigratoryData Architecture Guide</em>
 *  (<a target="_blank" href="http://migratorydata.com/documentation/pdf/Architecture.pdf">PDF</a>,
 *  <a target="_blank" href="http://migratorydata.com/documentation/html/Architecture/Architecture.html">HTML</a>)
 *  to learn about the syntax of the subjects.
 *
 * \param subjects An array of strings representing subjects.
 * \param conflationMillis 	An optional argument defining the number of milliseconds used to aggregate ("conflate") the messages for each subject
 * 							in the \c subjects list; default value is \c 0 meaning that no conflation will apply, and data publication will be
 * 							message-by-message with no message aggregation.
 */
- (void) subscribeWithConflation: (NSArray *)subjects conflationTimeMillis:(int)conflationMillis;


/**
 * \brief Unsubscribe from one or more subjects.
 *
 *  Unsubscribe from the subscribed subjects provided in the \c subjects parameter.
 *
 * \param subjects An array of strings representing subjects.
 *
 */
- (void) unsubscribe: (NSArray *)subjects;

/**
 * \brief Configure whether to use SSL/TLS encryption when connecting to a MigratoryData server.
 *
 * When using encryption you have to connect to the ports of the MigratoryData servers that are configured to listen for encrypted
 * connections. See the parameter <code>ListenEncrypted</code> in the <em>MigratoryData Configuration Guide</em>
 * (<a target="_blank" href="http://migratorydata.com/documentation/pdf/Configuration.pdf">PDF</a>,
 * <a target="_blank" href="http://migratorydata.com/documentation/html/Configuration/Configuration.html">HTML</a>).
 *
 * \param encryption
 *            Determine whether the client connects to the MigratoryData server using an encrypted SSL/TLS connection
 */
- (void) setEncryption: (BOOL)encryption;

/**
 * \brief Assign an authorization token to the client.
 *
 * To define which users of your application have access to which subjects, you will first have to set the parameter
 * \c Entitlement on \c true in the configuration file of the MigratoryData server ‚see the parameter \c Entitlement in the
 * <em>MigratoryData Configuration Guide</em>
 * (<a target="_blank" href="http://migratorydata.com/documentation/pdf/Configuration.pdf">PDF</a>,
 * <a target="_blank" href="http://migratorydata.com/documentation/html/Configuration/Configuration.html">HTML</a>).
 *
 * Then, you will have to use the entitlement-related part of the MigratoryData Extension API to allow or deny certain users to subscribe / publish
 * to certain subjects.
 *
 * \param token  A string representing an authorization token.
 */
- (void) setEntitlementToken: (NSString *)token;

/**
 * \brief Return the list of subscribed subjects.
 *
 * \return The list of strings representing the subscribed subjects.
 */
- (NSArray *) getSubjects;

/**
 *  \brief Define the number of failed attempts to connect to one or more MigratoryData servers
 *  before triggering a status notification \link NOTIFY_SERVER_DOWN \endlink.
 *
 * \param n The number of the failed attempts to connect to one or more MigratoryData servers before triggering a status notification
 *          \link NOTIFY_SERVER_DOWN \endlink; default value is <code>1</code>.
 */
- (void) setServersDownBeforeNotify: (int)n;

/**
 *  \brief Publish a message.
 *
 *  If the message includes a closure data, then a status notification will be provided via
 *  \link MigratoryDataListener::onStatus:info: \endlink to inform whether the message publication
 *  has been successful or failed.
 *
 * \param message A MigratoryDataMessage message
 */
- (void) publish: (MigratoryDataMessage *)message;

/**
 *  \brief Pause the API operation.
 *
 * If the application built with this API library enters into background, then it is 
 * recommended to use this API call. It will disconnect the user from the MigratoryData 
 * sever but will preserve the user's context (including the cluster definition and 
 * subscribed subjects) in order to reconnect to the cluster later when the API method 
 * \link MigratoryDataClient::resume \endlink is called.
 *
 * Moreover, if the cluster is configured with guaranteed message delivery, then when the user
 * will reconnect to the cluster using \link MigratoryDataClient::resume \endlink, it will get
 * all messages published since the \link MigratoryDataClient::pause \endlink method was called, 
 * provided however that the duration between the time when \link MigratoryDataClient::pause \endlink 
 * method was called and the \link MigratoryDataClient::resume \endlink method was called is 
 * less than the value defined by the parameter <code>CacheExpireTime</code> of the 
 * MigratoryData server (see details about this parameter in <em>MigratoryData Configuration Guide</em>
 * (<a target="_blank" href="http://migratorydata.com/documentation/pdf/Configuration.pdf">PDF</a>,
 * <a target="_blank" href="http://migratorydata.com/documentation/html/Configuration/Configuration.html">HTML</a>).
 */
- (void) pause;

/**
 *  \brief Resume the API operation.
 *
 * If the application was paused with the \link MigratoryDataClient::pause \endlink method, then
 * this API call will attempt to reconnect the user to the cluster. Also, if guaranteed message delivery
 * is enabled, this method also retrieves all messages published since the 
 * \link MigratoryDataClient::pause \endlink has been called provided that the duration between the 
 * time when \link MigratoryDataClient::pause \endlink method was called and the 
 * \link MigratoryDataClient::resume \endlink method was called is smaller than the value 
 * defined by the parameter <code>CacheExpireTime</code>.
 *
 * This method will be typically used when the application switches to foreground.
 */
- (void) resume;

/**
 * \brief Disconnect from the connected MigratoryData server and dispose the resources used by the connection.
 *
 * This method should be called when the connection is no longer necessary.
 */
- (void) dispose;

/**
 * \brief Define the maximum number of retries for the Quick Reconnect phase
 *
 * \param retries The maximum number of quick reconnect retries; default value is <code>3</code>.
 */
- (void) setQuickReconnectMaxRetries:(int) retries;

/**
 * \brief Define the number of seconds to wait before attempting to reconnect to the cluster after a connection failure is detected.
 *
 * <h5>Connection Failure Detection</h5>
 *
 * Connection failure is detected immediately for almost all users running modern browsers. For a few users running modern
 * browsers (and being subject to temporary, atypical network conditions) as well as for all users running older browsers
 * without WebSocket support, connection failure is detected after 30-40 seconds.
 *
 * <h5>Reconnection Phases and Policies</h5>
 *
 * When a connection failure is detected, the API will attempt to reconnect to the servers of the MigratoryData cluster as follows:
 * First, it will attempt to reconnect (up to a number of times as defined by \link MigratoryDataClient::setQuickReconnectMaxRetries() \endlink)
 * using small delays between retries (the Quick Reconnection phase). If the connection cannot be established after the Quick Reconnection phase,
 * then the API will attempt to reconnect less frequently according to the policy defined by \link MigratoryDataClient::setReconnectPolicy() \endlink.
 *
 * The delays between retries are computed acoording to the following algoritm where the values of the variables involved
 * are defined by the API methods having substantially the same names:
 *
 * <pre>
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
 * </pre>
 *
 * For a few users running modern browsers (and being subject to temporary, atypical network conditions) as well as for all users running older browsers
 * without WebSocket support, if <code>reconnectDelay</code> computed with the algorithm above is less than 10 seconds, then it is rounded to 10 seconds.
 *
 * \param seconds The number of seconds to wait before attempting to reconnect to the cluster; default value is <code>5</code> seconds.
 */
- (void) setQuickReconnectInitialDelay:(int) seconds;

/**
 * \brief Define the reconnect policy to be used after the Quick Reconnect phase.
 *
 * See \link MigratoryDataClient::setQuickReconnectInitialDelay() \endlink to learn
 * about the Quick Reconnect phase and the reconnect schedule for the policy defined
 * by this method.
 *
 * \param  policy The reconnect policy to be used after the Quick Reconnect phase. The possible values are
 *                \link CONSTANT_WINDOW_BACKOFF \endlink and \link TRUNCATED_EXPONENTIAL_BACKOFF \endlink;
 *                the default value is \link TRUNCATED_EXPONENTIAL_BACKOFF \endlink.
 */
- (void) setReconnectPolicy:(NSString* ) policy;

/**
 * \brief Define the time interval used for the reconnect schedule after the Quick Reconnect phase.
 *
 * See \link MigratoryDataClient::setQuickReconnectInitialDelay() \endlink to learn
 * about the Quick Reconnect phase and how the value defined by this API method is used.
 *
 * \param seconds A time interval expressed in seconds; default is <code>20</code> seconds.
 */
- (void) setReconnectTimeInterval:(int) seconds;

/**
 * \brief Define the maximum reconnect delay for the \link TRUNCATED_EXPONENTIAL_BACKOFF \endlink policy.
 *
 * See \link MigratoryDataClient::setQuickReconnectInitialDelay() \endlink to learn how the value defined by this API method is used.
 *
 * \param seconds The maximum reconnect delay when the policy \link TRUNCATED_EXPONENTIAL_BACKOFF \endlink is used; default value is 360 seconds.
 */
- (void) setReconnectMaxDelay:(int) seconds;

/**
 * \brief Assign an external token to a client.
 *
 * An external token which is provided by a client using this method is typically used by a MigratoryData plugin to enable that client to communicate with an external service.
 *
 * For example the MigratoryData plugin for Firebase needs an FCM token in order to be able to push notifications via the Firebase service to a mobile client. The mobile client
 * can provide the FCM token to the plugin using this method.
 *
 * @param externalToken A string representing an external token
 */
- (void) setExternalToken: (NSString *)externalToken;

- (void) setNumberOfHistoricalMessages:(int) number;

/// @cond
- (void) ping;
/// @endcond

@end
