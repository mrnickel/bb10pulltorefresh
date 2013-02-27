/*
 * Copyright (c) 2011-2012 Research In Motion Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.0

NavigationPane {
    id: navigationPane
    Page {
        Container {
            layout: DockLayout {}
            ImageView {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill

                imageSource: "asset:///images/background.png"
            }                        

            Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                
                PullToRefreshListView {
                    objectName: "tweetList"
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
                }
            }
        }
    }
}
