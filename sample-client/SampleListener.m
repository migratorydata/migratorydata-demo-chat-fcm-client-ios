#import "SampleListener.h"

@implementation SampleListener

- (id) initWithMessageField: (UITextField *)liveMessage statusField: (UITextField *)liveStatus {
	
	self = [super init];	
	if (self != nil) {
		messageTextField = liveMessage;
		statusTextField = liveStatus;        
	}
	
	return self;
}

- (void)onMessage:(MigratoryDataMessage *)message {
	id subject = [message getSubject];
	id content = [message getContent];
	
	NSLog(@"Got new message: subject = '%@', content = '%@'", subject, content);
	
    dispatch_async(dispatch_get_main_queue(), ^{
        messageTextField.text = [NSString stringWithFormat: @"%@ = %@\n", subject, content ];
    });
}

- (void) onStatus: (NSString *)status info:(NSString *)info {
    
	NSLog(@"Got new status notification: '%@'", status);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        statusTextField.text = [NSString stringWithFormat: @"%@ %@\n", status, info];
    });
}

- (void) dealloc {
    
	[super dealloc];
}

@end
