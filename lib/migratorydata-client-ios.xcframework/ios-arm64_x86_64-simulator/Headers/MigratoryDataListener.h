/*
 * Copyright (c) 2007-2020 Migratory Data Systems (http://migratorydata.com)
 * ALL RIGHTS RESERVED. Use is subject to license terms.
 */
 
#import "MigratoryDataMessage.h"

/**
 * The implementation of this interface will handle the messages received from the server for the subscribed subjects
 * as well as various status notifications.
 *
 *  Use the API method \link MigratoryDataClient.setListener() \endlink to register your listener implementation.
 */
@protocol MigratoryDataListener

/**
 * This method handles the real-time messages received from a MigratoryData server for the subscribed subjects.
 *
 * \param message An object of type \link MigratoryDataMessage \endlink .
 */
- (void)onMessage:(MigratoryDataMessage *)message;

/**
 * This method handles the status notifications.
 *
 * The possible values of the <code>status</code> parameter are:</p>
 *
 * \li <tt>\link NOTIFY_SERVER_UP \endlink</tt> indicates that the client successfully connected to the
 *      MigratoryData server provided in the detail information of the status notification
 *
 * \li <tt>\link NOTIFY_SERVER_DOWN \endlink</tt> indicates that the client was not able to connect to the
 *      MigratoryData server provided in the detail information of the status notification
 *
 * \li <tt>\link NOTIFY_DATA_SYNC \endlink</tt> indicates that, after a failover reconnection, the client
 *      successfully synchronized the subject given in the detail information of the status notification. Moreover, the client
 *      recovered all messages made available for that subject during the failover period, if any
 *
 * \li <tt>\link NOTIFY_DATA_RESYNC \endlink</tt> indicates that, after a failover reconnection, the client successfully
 *      * synchronized the subject given in the detail information; however, the potential messages made available for that subject during
 *      * the failover period have not been recovered, the client behaving like a new client which only received the most
 *      * recent retained message available for that subject
 *
 * \li <tt>\link NOTIFY_SUBSCRIBE_ALLOW \endlink</tt> indicates that the client -- identified with the token given
 *     in the argument of <tt>\link MigratoryDataClient.setEntitlementToken() \endlink</tt> -- is allowed to subscribe to the subject provided
 *     in the detail information of the status notification
 *
 * \li <tt>\link NOTIFY_SUBSCRIBE_DENY \endlink</tt> indicates that the client -- identified with the token given
 *     in the argument of <tt>\link MigratoryDataClient.setEntitlementToken() \endlink</tt> -- is not allowed to subscribe to the subject provided
 *     in the detail information of the status notification
 *
 * \li <tt>\link NOTIFY_PUBLISH_OK \endlink</tt> indicates that the client successfully published the message having
 *        the closure data provided in the detail information of the status notification
 *
 * \li <tt>\link NOTIFY_PUBLISH_FAILED \endlink</tt> indicates that the client was unable to publish the message having
 *        the closure data provided in the detail information of the status notification
 *
 * \li <tt>\link NOTIFY_PUBLISH_DENIED \endlink</tt> indicates that the client was unable to publish the message having
 *        the closure data provided in the detail information of the status notification because the client -- identified with the token given
 *        in the argument of <tt>\link MigratoryDataClient.setEntitlementToken() \endlink</tt> -- is not allowed to publish on the subject of the message
 *
 * \li \link MigratoryDataClient.NOTIFY_CONNECT_OK \endlink indicates that the client - identified with the
 * token given in the argument of \link MigratoryDataClient.setEntitlementToken() \endlink - is allowed to connect
 * for the reason provided by the <tt>info</tt> parameter
 *
 * \li \link MigratoryDataClient.NOTIFY_CONNECT_DENY \endlink indicates that the client - identified with the
 * token given in the argument of \link MigratoryDataClient.setEntitlementToken() \endlink - is denied to connect
 * for the reason provided by the <tt>info</tt> parameter
 *
 * \param status The type of the status notification (see the possible values above).
 *
 * \param info The detail information of the status notification.
 */
- (void)onStatus:(NSString *)status info:(NSString *)info;

@end
