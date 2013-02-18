import bb.cascades 1.0

ListView {                        
    signal refreshTriggered()
    property bool loading: false    
    id: refreshableList
    objectName: "refreshableList"
    leadingVisualSnapThreshold: 2.0
    
    listItemComponents: [
        ListItemComponent {			
            Container {
                id: itemRoot			                        
                preferredHeight: 200
                horizontalAlignment: HorizontalAlignment.Fill
                topPadding: 20
                leftPadding: 20
                rightPadding: 20
                bottomPadding: 20

                Label {			                                
                    text: ListItemData.fromUserName
                    textStyle.color: Color.create("#ffffff")
                    textStyle.fontWeight: FontWeight.Bold
                }

                Label {
                    preferredHeight: 200			
                    text: ListItemData.text	
                    multiline: true
                    textStyle.color: Color.create("#ffffff")
                }

            }
        }
    ]
    
   leadingVisual: RefreshHeader { 
        id: refreshHandler        
        onRefreshTriggered: {
            refreshableList.refreshTriggered();                            
        }   
    }
    
    onTouch: {
        if(event.touchType == 2) { //pulled and released
            refreshHandler.released();   
        }                              
    }
    
    onLoadingChanged: {
        refreshHandler.refreshing = refreshableList.loading;
    }
    
}