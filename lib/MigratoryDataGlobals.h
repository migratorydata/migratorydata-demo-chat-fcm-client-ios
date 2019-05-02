/*
 * Copyright (c) 2007-2014 Migratory Data Systems (http://migratorydata.com)
 * ALL RIGHTS RESERVED. Use is subject to license terms.
 */

/** \file MigratoryDataGlobals.h
 * 
 * \brief Include global constants and typedefs.
 */
 
/**
 * \brief Indicate that the client successfully connected to a MigratoryData server.
 *
 * This constant indicates that the client successfully connected to one of the MigratoryData servers defined with the API method
 * \link MigratoryDataClient::setServers: \endlink.
 */
extern NSString *NOTIFY_SERVER_UP;

/**
 * \brief Indicate that the client failed to connect to a MigratoryData server.
 *
 * This constant indicates that the client failed to connect to one of the MigratoryData servers defined with the API method
 * \link MigratoryDataClient::setServers: \endlink.
 */
extern NSString *NOTIFY_SERVER_DOWN;

/**
 * \brief After a failover reconnection, the client synchronized a subscribed subject with the latest message available for
 * that subject, as well as with all messages published during the failover for that subject.
 *
 * This constant indicates that the client successfully synchronized the subject provided in the detail information of
 * the status notification. Also, the potential messages published for that subject during the failover period have been
 * successfully retrieved at the moment of the reconnection.
 */
extern NSString *NOTIFY_DATA_SYNC;

/**
 * \brief After a failover reconnection, the client synchronized a subscribed subject with the latest message available for
 * that subject, but not with the potential messages published during the failover, therefore behaving as a new client.
 *
 * This constant indicates that the client successfully synchronized the subject provided in the detail information of
 * the status notification. However, the client was unable to get the messages published during the failover. Therefore, it
 * behaves like a new client which connects to the MigratoryData server at the moment of the failover reconnection.
 */
extern NSString *NOTIFY_DATA_RESYNC;

/**
 * \brief Indicate that the client was authorized to subscribe to a subject.
 *
 * This constant indicates that the client -- identified with the token defined with the API method
 * \link MigratoryDataClient::setEntitlementToken: \endlink -- is allowed to subscribe to the subject provided in the detail information
 * of the status notification.
 */
extern NSString *NOTIFY_SUBSCRIBE_ALLOW;

/**
 * \brief Indicate that the client was not authorized to subscribe to a subject.
 *
 * This constant indicates that the client -- identified with the token defined with the API method
 * \link MigratoryDataClient::setEntitlementToken: \endlink -- is not allowed to subscribe to the subject provided in the detail information
 * of the status notification.
 */
extern NSString *NOTIFY_SUBSCRIBE_DENY;

/**
 * \brief Indicate that the client was unable to publish a message because it is not allowed by your entitlement rules.
 *
 * This constant is used to indicate that the publication of the message, having the closure provided in the detail
 * information of the status notification, has failed. The publication failed because the client -- identified with
 * the token defined with the API method \link MigratoryDataClient::setEntitlementToken: \endlink -- is not allowed to
 * publish on the subject of the message.
 */
extern NSString *NOTIFY_PUBLISH_DENIED;

/**
 * \brief Indicate that the client was unable to publish a message because there is no client subscribed to the subject of the message.
 *
 * This constant is used to indicate that the publication of the message, having the closure provided in the detail
 * information of the status notification, has failed. The publication failed because there is no client
 * then subscribed to the subject of the message.
 */
extern NSString *NOTIFY_PUBLISH_NO_SUBSCRIBER;

/**
 * \brief Indicate that the client successfully published a message.
 *
 * This constant is used to indicate that the publication of the message, having the closure provided in the detail information of the
 * status notification, has succeeded.
 */
extern NSString *NOTIFY_PUBLISH_OK;

/**
 * \brief Indicate that the client was unable to publish a message.
 *
 * This constant is used to indicate that the publication of the message, having the closure provided in the detail
 * information of the status notification, has failed.
 */
extern NSString *NOTIFY_PUBLISH_FAILED;

/**
 * \brief A constant used to define the reconnect policy.
 *
 * See \link MigratoryDataClient::setQuickReconnectInitialDelay() \endlink for more details about this policy.
 */
extern NSString *CONSTANT_WINDOW_BACKOFF;

/**
 * \brief A constant used to define the reconnect policy.
 *
 * See \link MigratoryDataClient::setQuickReconnectInitialDelay() \endlink for more details about this policy.
 */
extern NSString *TRUNCATED_EXPONENTIAL_BACKOFF;


/**
 * \brief This class enumerates the MigratoryData logging levels.
 *
 * The available logging levels ordered by verbosity are:
 * <ul>
 *  <li>LOG_ERROR (less verbose)</li>
 *  <li>LOG_INFO</li>
 *  <li>LOG_DEBUG</li>
 *  <li>LOG_TRACE (most verbose)</li>
 * </ul>
 *
 * For production usage, we recommend the default <code>LOG_INFO</code> logging level.
 */
typedef NS_ENUM(NSInteger, LogType) {

    /**
     * \brief The <code>LOG_ERROR</code> level turns on the error logs of the API.
     */
    LOG_ERROR,

    /**
     * \brief The <code>LOG_INFO</code> level turns on the info, warning, and error logs of the API.
     */
    LOG_INFO,

    /**
     * \brief The <code>LOG_DEBUG</code> level turns on the debug, info, warning, and error logs of the API.
     */
    LOG_DEBUG,

    /**
     * \brief The <code>LOG_TRACE</code> level turns on all the logs of the API.
     */
    LOG_TRACE

};

