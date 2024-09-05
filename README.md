
### migratorydata-demo-chat-fcm-client-ios

Building a Real-time Chat App with iOS, MigratoryData, and Firebase Cloud Messaging (FCM)

Welcome to the documentation on building a real-time chat application using iOS, MigratoryData for real-time messaging, and Firebase Cloud Messaging (FCM) for notifications. In this guide, we'll walk you through the process of setting up iOS project, integrating Firebase Messaging.

### Prerequisites

Please read the following documentation.

Add Firebase to your iOS Project

	https://firebase.google.com/docs/ios/setup

Before we begin, ensure you have the following prerequisites installed and set up:

- MigratoryData Server 6.0.16 or later with Presence extension. see repo [migratorydata-demo-chat-fcm-plugin](https://github.com/migratorydata/migratorydata-demo-chat-fcm-plugin) for more details.
- Xcode 15.2 or later
- Firebase Account: Set up a new project in the [Firebase Console](https://console.firebase.google.com/) or use the existing project associated with the [fcm-plugin](https://github.com/migratorydata/migratorydata-demo-chat-fcm-plugin).


### Getting Started

1. Install [fcm-plugin]((https://github.com/migratorydata/migratorydata-demo-chat-fcm-plugin)) and run the Migratorydata server with presence extension. See the [migratorydata-demo-chat-fcm-plugin](https://github.com/migratorydata/migratorydata-demo-chat-fcm-plugin) for more details.

2. Clone this repository to your local machine.

3. Configuring Firebase Messaging.

The project has been pre-configured with all the essential libraries required for Firebase messaging functionality. The only missing component is the configuration file named `GoogleService-Info.plist`, which can be obtained from the Firebase dashboard under project settings. Once downloaded, add the `GoogleService-Info.plist` file to the root directory of your project.

For further guidance on configuring an iOS project with Firebase, you can refer to the documentation provided at this [link](https://firebase.google.com/docs/ios/setup).

4. Install necessary pods using the following command `pod install`, and open the project using the `sample-client.xcworkspace` file.

5. Configure the MigratoryData client options in file `AppDelegate.m` and update `SampleListener.m` with your custom notification message handling.

6. Launch the application on emulator or device.

### iOS API documentation

For further details, please refer the documentation at:

https://migratorydata.com/docs/client-api/ios/
