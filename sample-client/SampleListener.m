#import "SampleListener.h"

@implementation SampleListener

- (id) initWithMessageField: (UITextField *)liveMessage statusField: (UITextField *)liveStatus {
	
	self = [super init];	
	if (self != nil) {
		messageTextField = liveMessage;
		statusTextField = liveStatus;
        
        // notification = [[UILocalNotification alloc] init];
	}
	
	return self;
}

- (void)onMessage:(MigratoryDataMessage *)message {
	id subject = [message getSubject];
	id content = [message getContent];
	
	NSLog(@"Got new message: subject = '%@', content = '%@'", subject, content);
	
//    UIApplicationState state = [[UIApplication sharedApplication] applicationState];
//    if (state == UIApplicationStateBackground || state == UIApplicationStateInactive) {
//        [[UIApplication sharedApplication] cancelLocalNotification:notification];
//        notification.alertBody = [NSString stringWithFormat: @"%@ %@", subject, content];
//        notification.alertAction = @"Notification";
//        [[UIApplication sharedApplication] presentLocalNotificationNow:notification];
//    }
    
	messageTextField.text = [NSString stringWithFormat: @"%@ = %@\n", content, subject];
}

- (void) onStatus: (NSString *)status info:(NSString *)info {
    
	NSLog(@"Got new status notification: '%@'", status);
	
	statusTextField.text = [NSString stringWithFormat: @"%@ %@\n", status, info];
}

- (void) dealloc {
    
	[super dealloc];
}

@end
