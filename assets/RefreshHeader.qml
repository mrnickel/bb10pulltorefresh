import bb.cascades 1.0

Container {
    signal refreshTriggered
    id: refreshContainer
    property bool readyForRefresh: false
    property bool refreshing: false
    property string refreshedAt: ""
    horizontalAlignment: HorizontalAlignment.Fill
    layout: DockLayout {
    }
    
    //TODO: add last refreshed item

    Container {
        id: refreshStatusContainer
        opacity: 0.0
        horizontalAlignment: HorizontalAlignment.Fill
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
	        text: "Pull to Refresh"
	        verticalAlignment: VerticalAlignment.Center
	        textStyle.textAlign: TextAlign.Center
	        leftPadding: 0.0
	        topPadding: 10.0
	        bottomPadding: 10.0
	        textStyle.color: Color.create("#ffffff")
	        horizontalAlignment: HorizontalAlignment.Fill
	    }
    }

    Container {
        verticalAlignment: VerticalAlignment.Fill
        horizontalAlignment: HorizontalAlignment.Fill
        ActivityIndicator {
	        id: loadingIndicator
	        preferredWidth: 200.0
	        preferredHeight: 200.0
	        verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
	    }
    }
    
    Divider {
        opacity: 0.0
    }

    attachedObjects: [
        LayoutUpdateHandler {
            id: refreshHandler

            onLayoutFrameChanged: {
                id: layoutFrameChanged
                readyForRefresh = false;
                if (layoutFrame.y >= 0) {
                    refreshImage.rotationZ = 180;                    
                    if(!refreshing) {                              
                        readyForRefresh = true;
                    }                                    
                    refreshStatus.text = "Release to refresh"
                } else if (layoutFrame.y >= -100) {                    
                    refreshStatusContainer.opacity = 1.0;
//                    refreshImage.opacity = 1.0;
    	            if (refreshContainer.refreshedAt == "") {
    	                refreshStatus.text = "Pull to refresh"
    	            } else {
    	                refreshStatus.text = "Pull to Refresh. Last refreshed " + timeSince(refreshContainer.refreshedAt);
    	            }
                    
                    refreshImage.rotationZ = 0;
                } else {
                    //don't refresh
                    refreshStatusContainer.opacity = 0.0;
                    refreshImage.rotationZ = 0;
                }
            }
        }
    ]

    function released()
    {
        if (readyForRefresh) {
            readyForRefresh = false;
            refreshing = false;
            var tmpDate = new Date();      
            refreshContainer.refreshedAt = tmpDate.getTime()/1000; 
            refreshTriggered();
            
        }
    }
    
    onRefreshingChanged: {
        if (refreshing) {
            refreshStatusContainer.opacity = 0.0;
            loadingIndicator.running = true;
        } else {
            refreshStatusContainer.opacity = 1.0;
            loadingIndicator.running = false;            
        }
    }
    
    function timeSince(date) {
		var seconds = Math.floor(((new Date().getTime()/1000) - date)),
		interval = Math.floor(seconds / 31536000);
		
		if (interval > 1) return interval + "y ago";
		
		interval = Math.floor(seconds / 2592000);
		if (interval > 1) return interval + "m ago";
		
		interval = Math.floor(seconds / 86400);
		if (interval >= 1) return interval + "d ago";
		
		interval = Math.floor(seconds / 3600);
		if (interval >= 1) return interval + "h ago";
		
		interval = Math.floor(seconds / 60);
		if (interval > 1) return interval + "m ago";
		
		return "just now";
		//return Math.floor(seconds) + "s";
	}
}

