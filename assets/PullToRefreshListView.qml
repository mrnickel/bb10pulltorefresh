/* Forked from https://github.com/mrnickel/bb10pulltorefresh 
 * 
 * To use in QML, replace ListView{} by PullToRefreshListView {id: myListView}
 *
 * Add connection to signal:
 * onCreationCompleted: {myListView.refreshTriggered.connect(onRefreshTriggered);}
 *
 * function onRefreshTriggered() {
 *         myListView.loading = true;
 *         // Trigger refresh of your data
 *     }
 *
 * When refresh is done, set loading to false:
 * function onPodcastLoaded(rp) {     
 *     myListView.loading = false; }
 *
 */

import bb.cascades 1.0

ListView {
    signal refreshTriggered()
    property bool loading: false
    id: refreshableList
    leadingVisualSnapThreshold: 2.0
    leadingVisual: RefreshHeader {
        id: refreshHandler
        onRefreshTriggered: {
            refreshableList.refreshTriggered();
        }
    }
    onTouch: {
        refreshHandler.onListViewTouch(event);
    }
    onLoadingChanged: {
        refreshHandler.refreshing = refreshableList.loading;
                 
        if(!refreshHandler.refreshing) {
            // If the refresh is done 
            // Force scroll to top to ensure that all items are visible
            scrollToPosition(ScrollPosition.Beginning, ScrollAnimation.None);
        }
    }
}
