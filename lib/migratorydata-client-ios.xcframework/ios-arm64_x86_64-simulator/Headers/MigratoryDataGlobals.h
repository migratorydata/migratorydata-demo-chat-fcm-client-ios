/*
 * Copyright (c) 2007-2020 Migratory Data Systems (http://migratorydata.com)
 * ALL RIGHTS RESERVED. Use is subject to license terms.
 */

/** \file MigratoryDataGlobals.h
 * 
 * \brief Include global constants and typedefs.
 */
 
/**
 * A constant which indicates that the client successfully connected to a MigratoryData server.
 */
extern NSString *NOTIFY_SERVER_UP;

/**
 * A constant which indicates that the client failed to connect to a MigratoryData server.
 */
extern NSString *NOTIFY_SERVER_DOWN;

/**
 * A constant which indicates that after a failover reconnection, the client successfully synchronized a subscribed
 * subject with the latest retained message available for that subject, as well as with all messages made available
 * during the failover period for that subject.
 */
extern NSString *NOTIFY_DATA_SYNC;

/**
 * A constant which indicates that after a failover reconnection, the client successfully synchronized a subscribed
 * subject with the latest retained message available for that subject, but not with the potential messages made
 * available during the failover period, therefore behaving as a new client.
 */
extern NSString *NOTIFY_DATA_RESYNC;

/**
 * A constant which indicates that the client was unable to publish a message because the size of the message
 * exceeds the message size limit allowed by the server (see the server parameter \c MAX_MESSAGE_SIZE).
 */
extern NSString *NOTIFY_MESSAGE_SIZE_LIMIT_EXCEEDED;

/**
 * A constant which indicates that the client was authorized to subscribe to a subject.
 */
extern NSString *NOTIFY_SUBSCRIBE_ALLOW;

/**
 * A constant which indicates that the client was not authorized to subscribe to a subject.
 */
extern NSString *NOTIFY_SUBSCRIBE_DENY;

/**
 * A constant which indicates that the client successfully published a message.
 */
extern NSString *NOTIFY_PUBLISH_OK;

/**
 * A constant which indicates that the client was unable to publish a message.
 */
extern NSString *NOTIFY_PUBLISH_FAILED;

/**
 * A constant which indicates that the client was unable to publish a message because it is not allowed by the
 * entitlement system.
 */
extern NSString *NOTIFY_PUBLISH_DENIED;

/**
 * A constant used to define the reconnect policy.
 *
 * See \link MigratoryDataClient.setQuickReconnectInitialDelay() \endlink for more details about this policy.
 */
extern NSString *CONSTANT_WINDOW_BACKOFF;

/**
 * A constant used to define the reconnect policy.
 *
 * See \link MigratoryDataClient.setQuickReconnectInitialDelay() \endlink for more details about this policy.
 */
extern NSString *TRUNCATED_EXPONENTIAL_BACKOFF;

/**
 * A constant used to define the transport type.
 *
 * See \link MigratoryDataClient.setTransport() \endlink for more details about this policy.
 */
extern NSString *TRANSPORT_HTTP;

/**
 * A constant used to define the transport type.
 *
 * See \link MigratoryDataClient.setTransport() \endlink for more details about this policy.
 */
extern NSString *TRANSPORT_WEBSOCKET;

/**
 * A constant which indicates that the client was authorized to connect using the entitlement token defined on the client side.
 *
 * NOTE: This notification applies when using a <tt>Custom</tt> authorization extension built with the
 * MigratoryData Authorization Extensions API version 2 or later. For the entitlement methods <tt>None</tt>, <tt>Basic</tt>,
 * or <tt>Custom</tt> authorization extension built with the previous version of the MigratoryData Authorization Extension API,
 * this notification is always sent no matter the entitlement token is valid or not, the verification of the entitlement
 * token being made only during subscribe and publish operations.
 */
extern NSString *NOTIFY_CONNECT_OK;

/**
 * A constant which indicates that the client was denied to connect using the entitlement token defined on the client side.
 *
 * NOTE: This notification applies when using a <tt>Custom</tt> authorization extension built with the
 * MigratoryData Authorization Extension API version 2 or later. For the entitlement methods <tt>None</tt>, <tt>Basic</tt>,
 * or <tt>Custom</tt> authorization extension built with the previous version of the MigratoryData Authorization Extension API,
 * this notification is never sent no matter the entitlement token is valid or not, the verification of the entitlement
 * token being made only during subscribe and publish operations.
 */
extern NSString *NOTIFY_CONNECT_DENY;


/**
 * This class enumerates the MigratoryData logging levels.
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
typedef NS_ENUM(NSInteger, MigratoryDataLogLevel) {

    /**
     * The <code>LOG_ERROR</code> level turns on the error logs of the API.
     */
    LOG_ERROR,

    /**
     * The <code>LOG_INFO</code> level turns on the info, warning, and error logs of the API.
     */
    LOG_INFO,

    /**
     * The <code>LOG_DEBUG</code> level turns on the debug, info, warning, and error logs of the API.
     */
    LOG_DEBUG,

    /**
     * The <code>LOG_TRACE</code> level turns on all the logs of the API.
     */
    LOG_TRACE
};

/**
 * The quality of service (QoS) levels for MigratoryData messaging.
 */
typedef NS_ENUM(NSInteger, MigratoryDataQoS) {
    /**
     * The <code>MigratoryDataQoS.STANDARD</code> should be used for noncritical messages which will not be included in the cache
     * of the MigratoryData cluster. In this way, after a connection recovery, a client will not receive as part of
     * the recovery process the messages with <code>MigratoryDataQoS.STANDARD</code>.
     *
     * <p>
     *     Note: This QoS level corresponds to the <code>at-most-once</code> delivery semantics.
     * </p>
     */
    STANDARD = 0,

    /**
     * The <code>MigratoryDataQoS.GUARANTEED</code> should be used for critical messages which will be included in the cache of
     * the MigratoryData cluster. In this way, after a connection recovery, a client will receive as part of the
     * recovery process the messages with <code>MigratoryDataQoS.GUARANTEED</code>.
     *
     * <p>
     *     Note: This QoS level corresponds to the <code>at-least-once</code> delivery semantics. Also, it might
     *     correspond to the <code>exactly-once</code> delivery semantics provided that subscribers are responsible
     *     for filtering out duplicate receptions, if it at all matters for the application. Typically, a small
     *     buffer containing the identifiers of recently-received messages is sufficient for this task.
     * </p>
     */
    GUARANTEED
};

/**
 * The message type received from MigratoryData server.
 */
typedef NS_ENUM(NSInteger, MigratoryDataMessageType) {
    /**
     * The message from the server is snapshot type.
     */
    SNAPSHOT = 1,

    /**
     * The message from the server is update type.
     */
    UPDATE,

    /**
     * The message from the server is recovered type.
     */
    RECOVERED,

    /**
     * The message from the server is historical type.
     */
    HISTORICAL
};
