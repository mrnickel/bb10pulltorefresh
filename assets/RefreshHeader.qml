import bb.cascades 1.0

Container {
    signal refreshTriggered
    id: refreshContainer
    property string readyForRefresh: "no"
    property string refreshing: "no"
    
    ImageView {
        id: refreshImage
        imageSource: "asset:///images/refresh.png"   
        verticalAlignment: VerticalAlignment.Center
        horizontalAlignment: HorizontalAlignment.Center
        preferredHeight: 75.0
        preferredWidth: 75.0
    }

    Label {
        id: refreshStatus
        text: "Pull To Refresh"
        opacity: 0.0
        verticalAlignment: VerticalAlignment.Center
        textStyle.textAlign: TextAlign.Center
        leftPadding: 0.0
        topPadding: 10.0
        bottomPadding: 10.0
        textStyle.color: Color.create("#ffffff")
        horizontalAlignment: HorizontalAlignment.Fill
    }
    Divider {
        opacity: 0.0
    }

    attachedObjects: [
        LayoutUpdateHandler {
            id: refreshHandler

            onLayoutFrameChanged: {
                id: layoutFrameChanged
                readyForRefresh = "no";
                if (layoutFrame.y >= 0) {
                    refreshImage.rotationZ = 180;                    
                    if(refreshing == "no") {                              
                        readyForRefresh = "yes";
                    }
                    refreshStatus.text = "Release to refresh"
                } else if (layoutFrame.y >= -100) {                    
                    refreshStatus.opacity = 1.0;
                    refreshStatus.text = "Pull to refresh"
                    refreshImage.rotationZ = 0;
                } else {
                    //don't refresh
                    refreshStatus.opacity = 0.0;
                    refreshImage.rotationZ = 0;
                }
            }
        }
    ]
    horizontalAlignment: HorizontalAlignment.Fill
    function released()
    {
        console.log(readyForRefresh);
        if (readyForRefresh == "yes") {
            readyForRefresh = "no";
            refreshing = "yes";
            refreshTriggered();            
        } else {
            console.log("It was released, but don't do the refresh");
        }

        console.log("Set to false: "+readyForRefresh);
    }
}

