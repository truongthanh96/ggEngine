/**
 * Created by Knight of k9 on 12/11/2016.
 */
var HierarchyEditor = function () {
    var hierarchyPanel = $("#gg-info-hierarchy");
    var navTab = $("#gg-info-hierarchy-nav-tab");
    var hierarchyListPanel = $("#gg-hierarchy-list");
    //<a href="#" class="list-group-item">Item 1</a>
    //<div class="list-group">

    // var hierarchyList = [];
    var hObjectList = [];
    var id = 0;
    var currentHTileMap = null;
    this.add = {};
    this.add.group = function(){
        var group = new Group();
        group._item = game.add.group();
        my.hierarchy._add(group);
        var div = createLine(group._hierarchyId,group._name);
        hierarchyListPanel.append(div);
        return group;
    };
    this.add.tilemap = function(){
        var tileMap = new TileMap();
        tileMap._item = game.add.tilemap();
        my.hierarchy._add(tileMap);
        var div = createLine(tileMap._hierarchyId,tileMap._name);
        hierarchyListPanel.append(div);
        currentHTileMap = tileMap;
        return tileMap;
    };
    this.add.staticTile = function(x,y,layer,tileMap){
        var staticTile = new StaticTile();
        staticTile.layer = layer;
        if(currentHTileMap._item !== tileMap){
            ggConsole.alertNotification("Error","Current Tile Map different from add tile map!");
            return null;
        }
        var idX = layer.getTileX(x);
        var idY = layer.getTileY(y);
        staticTile.x = x;
        staticTile.y = y;
        staticTile.idX = idX;
        staticTile.idY = idY;

        staticTile._item = tileMap.getTile(idX, idY, layer);
        staticTile.parent = currentHTileMap;
        if(!currentHTileMap.addTypeTile(staticTile)){
            my.hierarchyIdCount-=1;
            return null;
        }
        // staticTile._item.alpha = 0.5;
        layer.dirty = true;

        var div = createChild(createHierarchyDiv(my.hierarchyIdDict[staticTile._hierarchyId]));
        var parentDiv = $("#hierarchy-"+ currentHTileMap._hierarchyId);
        parentDiv.append(div);
        // reloadHierarchy();
        return staticTile;

    };





    this.setActive = function(isActive){
        if(isActive){
            hierarchyPanel.css("display","block");
            navTab.addClass("active");
        }else{
            hierarchyPanel.css("display","none");
            navTab.removeClass("active");
        }

    };
    this.clearAll = function(){
        hierarchyListPanel.html("");
        currentHTileMap = null;
        // hierarchyList = [];
        // hObjectList = [];
        // id = 0;
    };
    this.addObjectToHierarchy = function (name, object) {
        var hierarchyObject = new HierarchyObject();
        hierarchyObject.id = id++;
        hierarchyObject.name = name;
        hierarchyObject.item = object;
        hierarchyObject.parent = null;
        hierarchyList.push(hierarchyObject);
        hObjectList.push(hierarchyObject);
        return hierarchyObject;
    };
    this.addObjectToHObject = function(name, object,hParent){
        var hierarchyObject = new HierarchyObject();
        hierarchyObject.id = id++;
        hierarchyObject.name = name;
        hierarchyObject.item = object;
        hierarchyObject.parent = hParent;
        hObjectList.push(hierarchyObject);
        hParent.childList.push(hierarchyObject);
    };
    this.removeHObjectFromHObject = function(hObject, hParent){
        for(var i  = 0;i>hParent.childList.length;i++){
            var childHObject = hParent.childList[i];
            if(childHObject.id === hObject.id){
                hParent.childList.splice(i,1);
                break;
            }
        }
    };
    this.removeObjectFromHObject = function(name, hParent){
        for(var i  = 0;i>hParent.childList.length;i++){
            var childHObject = hParent.childList[i];
            if(childHObject.name === name){
                hParent.childList.splice(i,1);
                break;
            }
        }
    };

    this.removeAllObjectFromHObject = function(name, hParent){
        for(var i  = 0;i>hParent.childList.length;i++){
            var childHObject = hParent.childList[i];
            if(childHObject.name === name){
                hParent.childList.splice(i,1);
            }
        }
    };
    this.removeObject = function (name, object) {

    };
    this.removeAllObject = function () {
        while(hierarchyList.length){
            hierarchyList.pop();
        }
    };
    this.updateHierarchy = function () {
        reloadHierarchy();
    };

    this.handleRemoveClick = function(hObjectId){
        var isReload = false;
        var hObject = my.hierarchyIdDict[hObjectId];
        if(hObject){
            if(hObject.callDestroy){
                if(hObject.callDestroy()){
                    isReload = true;
                }
            }else{
                ggConsole.alertNotification("Warning",hObject.type+" has no destroy method!");
                return false;
            }
        }else{
            return false;
        }
        if(isReload){
           reloadHierarchy();
        }
        return true;
        // for(var i = 0;i<hObjectList.length; i++){
        //     if(hObjectList[i].id === hObjectId){
        //         if(!hObjectList[i].item.callDestroy()) return;
        //         if(hObjectList[i].parent != null){
        //             for(var t = 0;t<hObjectList[i].parent.childList.length;t++){
        //                 if(hObjectList[i].parent.childList[t].id === hObjectId){
        //                     hObjectList[i].parent.childList.splice(t,1);
        //                     break;
        //                 }
        //             }
        //         }else{
        //             hierarchyList.splice(hierarchyList.indexOf(hObjectList[i]),1);
        //         }
        //         hObjectList.splice(i,1);
        //         break;
        //     }
        // }
        // reloadHierarchy();
    };

    /**
     * Private function
     */


    var reloadHierarchy = function () {
        hierarchyListPanel.html("");
        var div = "";
        for (var i = 0; i < my.hierarchy._childList.length; i++) {
            div += createHierarchyDiv(my.hierarchy._childList[i]);
        }
        hierarchyListPanel.html(div);
        if(sceneEditor && sceneEditor.editState) sceneEditor.editState.getCurrentLayer().dirty = true;
    };

    var createHierarchyDiv = function (hObject) {
        var div = createLine(hObject._hierarchyId, hObject._name);
        for(var i = 0;i<hObject._childList.length;i++){
            div += createChild(createHierarchyDiv(hObject._childList[i]));
        }
        return div;
    };

    var createLine = function (id, name) {
        return '<div id="hierarchy-'+id+'"><a  class="list-group-item">' + name
            +'<i onclick="hierarchyEditor.handleRemoveClick('+id+')" class="glyphicon glyphicon-remove gg-hierarchy-delete"></i>'
            + '</a></div>';
    };
    var createChild = function (content) {
        return '<div class="list-group">'
            + content
            + '</div>';
    };

    var init = function(){
        var menu = [{
            name: 'Create Group',
            // img: 'images/create.png',
            title: 'Create Group',
            fun: function () {
                sceneEditor.editState.showCreateGroup();
            }
        }];
        $('#gg-info-hierarchy').contextMenu(menu,{triggerOn:'contextmenu'});
    };
    init();
};

function _HierarchyObject() {
    this.id = "";
    this.name = "";
    this.item = null;
    this.parent = null;
    this.childList = [];
    this.nextObject = null;
    this.prevObject = null;

}