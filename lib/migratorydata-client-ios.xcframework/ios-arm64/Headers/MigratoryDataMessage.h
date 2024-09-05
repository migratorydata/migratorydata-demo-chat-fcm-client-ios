/*
 * Copyright (c) 2007-2020 Migratory Data Systems (http://migratorydata.com)
 * ALL RIGHTS RESERVED. Use is subject to license terms.
 */
#import <Foundation/Foundation.h>
#import "MigratoryDataGlobals.h"

/**
 * Represent a message
 */
@interface MigratoryDataMessage : NSObject {
@private
	NSString *_subject;
	NSString *_content;
    NSString *_closure;
    NSString *_replySubject;
    bool _retained;
    bool _compression;
    MigratoryDataQoS _qos;
	MigratoryDataMessageType _messageType;
	int _seq;
	int _epoch;
}

/**
 * Create a MigratoryDataMessage object.
 *
 * \param subject The subject of the message
 * \param content The content of the message
 */
- (id) init: (NSString *)subject content:(NSString *)content;

/**
 * Create a MigratoryDataMessage object.
 *
 * \param subject The subject of the message
 * \param content The content of the message
 * \param closure The closure of the message (OPTIONAL)
 */
- (id) init: (NSString *)subject content:(NSString *)content closure:(NSString *)closure;

/**
 * Create a MigratoryDataMessage object.
 *
 * \param subject The subject of the message
 * \param content The content of the message
 * \param closure The closure of the message (OPTIONAL)
 * \param qos       the QoS level of the message; the default is <code>MigratoryDataQoS.GUARANTEED</code> (OPTIONAL)
 * \param retained  indicate whether or not the message should be/was retained by the server; the default is <code>true</code> (OPTIONAL)
 */
- (id) init: (NSString *)subject content:(NSString *)content closure:(NSString *)closure qos:(MigratoryDataQoS)qos retained:(bool)retained;

/**
 * Create a MigratoryDataMessage object
 *
 * If a reply subject is attached to a message, the message acts as a request message. The clients which receive a
 * request message will be able to reply by sending back one or more messages having as subject the reply subject.
 *
 * <p>
 *     Note: If the reply subject is not already subscribed, it will be subscribed by the library implicitly, and it
 *     can be reused for request/reply interactions (and even for receiving multiple replies to one request). When
 *     it is not needed anymore, it should be unsubscribed explicitly.
 * </p>
 *
 * \param subject The subject of the message
 * \param content The content of the message
 * \param closure The closure of the message (OPTIONAL)
 * \param qos       the QoS level of the message; the default is <code>MigratoryDataQoS.GUARANTEED</code> (OPTIONAL)
 * \param retained  indicate whether or not the message should be/was retained by the server; the default is <code>true</code> (OPTIONAL)
 * \param replySubject   the reply subject of the message (OPTIONAL)
 *
 */
- (id) init: (NSString *)subject content:(NSString *)content closure:(NSString *)closure qos:(MigratoryDataQoS)qos retained:(bool)retained replySubject:(NSString *)replySubject;

/// @cond
- (id) init: (NSString *)subject content:(NSString *)content closure:(NSString *)closure retained:(bool)retained qos:(MigratoryDataQoS)qos replySubject:(NSString *)replySubject messageType:(MigratoryDataMessageType)messageType seq:(int)seq epoch:(int)epoch;
/// @endcond

/**
 * Get the subject of the message
 *
 * \return A string representing the subject of the message
 */
- (NSString *) getSubject;

/**
 * Get the content of the message
 *
 * \return A string representing the content of the message
 */
- (NSString *) getContent;

/**
 * Get the closure of the message
 *
 * \return The closure data of the message
 */
- (NSString *) getClosure;

/**
 * Indicate whether or not the message should be/was retained by the server.
 *
 * \return  true if the message should be, or was, retained by the server
 */
- (bool) isRetained;

/**
 * Get the subject to be used to reply to this message.
 *
 * A client which receives a message containing a reply subject should interpret the message
 * as a request. It has the option to use the reply subject - extracted from the message with
 * this method - to send a reply.
 *
 * \return The subject to be used to reply to this message.
 */
- (NSString *) getReplySubject;

/**
 * Get the QoS level of the message.
 *
 * \return the QoS level of the message
 */
- (MigratoryDataQoS) getQos;

/**
 * Get the MessageType of the message.
 *
 * \return the message type of the message
 */
- (MigratoryDataMessageType) getMessageType;

/**
 * Set whether to compress the content of the message or not.
 *
 *  <p>
 *      Note: If compression is enabled with this method but the size of the content of the message is smaller than
 *      the size of compressed content, then the message will be sent uncompressed to save bandwidth and CPU cycles
 *      with the decompression on the receiver side.
 *  </p>
 *
 * @param compressed if \c true, the content of the message will be published in ZLIB-compressed format; if \c false
 *                  no compression format will be used; the default value is \c false.
 */
- (void) setCompressed:(bool)compressed;

/**
 * Indicate whether or not the message should be/was compressed.
 *
 * @return Return whether or not the message should be/was compressed. If the received message was compressed, the
 * library automatically decompresses its content without any additional code.
 */
- (bool)isCompressed;


/// @cond
- (int) getSeq;

- (int) getEpoch;
/// @endcond
@end
