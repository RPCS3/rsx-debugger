import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 1920
    height: 1080
    title: qsTr("RSX Debugger")

    SplitView {
        id: splitView1
        anchors.fill: parent

        ScrollView
        {
            ListView {
                width: 130
                anchors.fill: parent.fill
                model: commandList

                delegate: Item {
                    x: 5
                    width: 80
                    height: 40

                    Row {
                        Text {
                            text: model.modelData
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        spacing: 10
                    }
                }
            }
        }

        ScrollView
        {
            ListView {
                id: listView1
                width: 130
                anchors.fill: parent.fill
                model: stateList
                delegate: Item {
                    x: 5
                    width: 80
                    height: 40

                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked: {
                            listView1.currentIndex = index
                        }
                    }

                    Row {
                        id: row1
                        Text {
                            text: model.modelData.name
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        spacing: 10
                    }
                }
            }
        }

        TabView {
            id: tabView1
            anchors.fill: parent.fill
            Tab {
                title: "Transform program"

                TextArea {
                    id: textArea1
                    text: listView1.model[listView1.currentIndex].transformProgram
                    readOnly: true
                }
            }

            Tab {
                title: "Shader program"

                TextArea {
                    id: textArea2
                    text: listView1.model[listView1.currentIndex].shaderProgram
                    readOnly: true
                }
            }

            Tab {
                title: "Input Assembly"

                Flow {
                    GroupBox {
                        title:"Offseting"
                        Column {
                            Label {
                                text: "Scale: " + listView1.model[listView1.currentIndex].polyOffsetScale
                            }
                            Label {
                                text: "Bias: " + listView1.model[listView1.currentIndex].polyOffsetBias
                            }
                            Label {
                                text: "Point: " + listView1.model[listView1.currentIndex].polyOffsetPoint
                            }
                            Label {
                                text: "Line: " + listView1.model[listView1.currentIndex].polyOffsetLine
                            }
                            Label {
                                text: "Fill: " + listView1.model[listView1.currentIndex].polyOffsetFill
                            }
                        }
                    }
                    GroupBox {
                        title:"Viewport"
                        Column {
                            GroupBox {
                                title:"Scale"
                                Column {
                                    Label {
                                        text:"X: " + listView1.model[listView1.currentIndex].viewportScaleX
                                    }
                                    Label {
                                        text:"Y: " + listView1.model[listView1.currentIndex].viewportScaleY
                                    }
                                    Label {
                                        text:"Z: " + listView1.model[listView1.currentIndex].viewportScaleZ
                                    }
                                    Label {
                                        text:"W: " + listView1.model[listView1.currentIndex].viewportScaleW
                                    }
                                }
                            }
                            GroupBox {
                                title:"Offset"
                                Column {
                                    Label {
                                        text:"X: " + listView1.model[listView1.currentIndex].viewportOffsetX
                                    }
                                    Label {
                                        text:"Y: " + listView1.model[listView1.currentIndex].viewportOffsetY
                                    }
                                    Label {
                                        text:"Z: " + listView1.model[listView1.currentIndex].viewportOffsetZ
                                    }
                                    Label {
                                        text:"W: " + listView1.model[listView1.currentIndex].viewportOffsetW
                                    }
                                }
                            }
                        }
                    }
                    GroupBox {
                        title:"Indexing"
                        Column {
                            Label {
                                text: "Vertex base offset: " + listView1.model[listView1.currentIndex].vertexBaseOffset
                            }
                            Label {
                                text: "Vertex base index: " + listView1.model[listView1.currentIndex].vertexBaseIndex
                            }
                            Label {
                                text:"Restart Index enabled: " + listView1.model[listView1.currentIndex].restartIndexEnabled
                            }
                            Label {
                                text:"Restart Index: " + listView1.model[listView1.currentIndex].restartIndex
                            }
                            ScrollView {
                                GroupBox {
                                    title:"Index List"
                                    ListView {
                                        width:100
                                        height:100
                                        model: listView1.model[listView1.currentIndex].indexList
                                        delegate: Item {
                                            x: 5
                                            width: 80
                                            height: 40

                                            Row {
                                                Text {
                                                    text: model.modelData
                                                }
                                                spacing: 10
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    GroupBox {
                        title:"Fog"
                        Column {
                            Label {
                                text:"fog P0: " + listView1.model[listView1.currentIndex].fogP0
                            }
                            Label {
                                text:"fog P1: " + listView1.model[listView1.currentIndex].fogP1
                            }
                        }
                    }
                    Label {
                        text:"2 sided lighting: " + listView1.model[listView1.currentIndex].twoSidedLighting
                    }
                    Label {
                        text:"Cull: " + listView1.model[listView1.currentIndex].cullEnabled
                    }
                }
            }

            Tab {
                title: "Output merge"
                Flow {
                    GroupBox {
                        title:"Viewport"
                        Column {
                            Label {
                                text:"origin x: " + listView1.model[listView1.currentIndex].ViewportOriginX
                            }
                            Label {
                                text:"origin y: " + listView1.model[listView1.currentIndex].ViewportOriginY
                            }
                            Label {
                                text:"width: " + listView1.model[listView1.currentIndex].ViewportWidth
                            }
                            Label {
                                text:"height: " + listView1.model[listView1.currentIndex].ViewportHeight
                            }
                        }
                    }
                    GroupBox {
                        title:"Scissor"
                        Column {
                            Label {
                                text:"origin x: " + listView1.model[listView1.currentIndex].ScissorOriginX
                            }
                            Label {
                                text:"origin y: " + listView1.model[listView1.currentIndex].ScissorOriginY
                            }
                            Label {
                                text:"width: " + listView1.model[listView1.currentIndex].ScissorWidth
                            }
                            Label {
                                text:"height: " + listView1.model[listView1.currentIndex].ScissorHeight
                            }
                        }
                    }
                    GroupBox {
                        title:"Logic Op"
                        Column {
                            Label {
                                text: "Enabled: " + listView1.model[listView1.currentIndex].logicOp
                            }
                            Label {
                                text: "Func: " + listView1.model[listView1.currentIndex].logicFunc
                            }
                        }
                    }
                    GroupBox {
                        title:"Alpha Test"
                        Column {
                            Label {
                                text: "Enabled: " + listView1.model[listView1.currentIndex].alphaTest
                            }
                            Label {
                                text: "Func: " + listView1.model[listView1.currentIndex].alphaFunc
                            }
                            Label {
                                text: "Ref: " + listView1.model[listView1.currentIndex].alphaRef
                            }
                        }
                    }
                    GroupBox {
                        title:"Depth"
                        Column {
                            Label {
                                text:"Test: " + listView1.model[listView1.currentIndex].depthTest
                            }
                            Label {
                                text:"Func: " + listView1.model[listView1.currentIndex].depthFunc
                            }
                            Label {
                                text:"Write: " + listView1.model[listView1.currentIndex].depthWrite
                            }
                            Label {
                                text:"Bound: " + listView1.model[listView1.currentIndex].depthBound
                            }
                        }
                    }
                    GroupBox {
                        title:"Stencil Test"
                        Column {
                            Label {
                                text: "Enabled: " + listView1.model[listView1.currentIndex].stencilTest
                            }
                            Label {
                                text: "2 sided: " + listView1.model[listView1.currentIndex].twoSidedStencil
                            }
                        }
                    }
                    GroupBox {
                        title:"Color Mask"
                        Column {
                            Label {
                                text: "A: " + listView1.model[listView1.currentIndex].colorMaskA
                            }
                            Label {
                                text: "R: " + listView1.model[listView1.currentIndex].colorMaskR
                            }
                            Label {
                                text: "G: " + listView1.model[listView1.currentIndex].colorMaskG
                            }
                            Label {
                                text: "B: " + listView1.model[listView1.currentIndex].colorMaskB
                            }
                        }
                    }
                    GroupBox {
                        title:"Blend"
                        Column {
                            Label {
                                text: "Enabled: " + listView1.model[listView1.currentIndex].blendEnabled
                            }
                            Label {
                                text: "Surface 1: " + listView1.model[listView1.currentIndex].blendSurface1
                            }
                            Label {
                                text: "Surface 2: " + listView1.model[listView1.currentIndex].blendSurface2
                            }
                            Label {
                                text: "Surface 3: " + listView1.model[listView1.currentIndex].blendSurface3
                            }
                            GroupBox {
                                title:"RGB"
                                Column {
                                    Label {
                                        text: "Equation: " + listView1.model[listView1.currentIndex].blendEquationRGB
                                    }
                                    Label {
                                        text: "Src Factor: " + listView1.model[listView1.currentIndex].blendSFactorRGB
                                    }
                                    Label {
                                        text: "Dst Factor: " + listView1.model[listView1.currentIndex].blendDFactorRGB
                                    }
                                }
                            }
                            GroupBox {
                                title:"Alpha"
                                Column {
                                    Label {
                                        text: "Equation: " + listView1.model[listView1.currentIndex].blendEquationA
                                    }
                                    Label {
                                        text: "Src Factor: " + listView1.model[listView1.currentIndex].blendSFactorA
                                    }
                                    Label {
                                        text: "Dst Factor: " + listView1.model[listView1.currentIndex].blendDFactorA
                                    }
                                }
                            }
                        }
                    }
                    GroupBox {
                        title:"Smooth"
                        Column {
                            Label {
                                text: "Line: " + listView1.model[listView1.currentIndex].lineSmoothEnabled
                            }
                            Label {
                                text: "Poly: " + listView1.model[listView1.currentIndex].polySmoothEnabled
                            }
                        }
                    }
                }
            }

            Tab {
                title: "Surface"
                Flow
                {
                    GroupBox {
                        title:"Clip"
                        Column
                        {
                            Label
                            {
                                text:"X: " + listView1.model[listView1.currentIndex].originX
                            }
                            Label
                            {
                                text:"Y: " + listView1.model[listView1.currentIndex].originY
                            }
                            Label
                            {
                                text:"Width: " + listView1.model[listView1.currentIndex].widthRole
                            }

                            Label
                            {
                                text:"Height: " + listView1.model[listView1.currentIndex].heightRole
                            }
                        }
                    }
                    GroupBox {
                        title:"Layout"
                        Column
                        {
                            Label
                            {
                                text:"Width: " + listView1.model[listView1.currentIndex].surfaceWidth
                            }
                            Label
                            {
                                text:"Height: " + listView1.model[listView1.currentIndex].surfaceHeight
                            }
                            Label
                            {
                                text:"Depth format: " + listView1.model[listView1.currentIndex].surfaceDepthFormat
                            }
                            GroupBox {
                                title: "Color"
                                Column {
                                    Label
                                    {
                                        text:"Format: " + listView1.model[listView1.currentIndex].surfaceColorFormat
                                    }
                                    Label
                                    {
                                        text:"Target: " + listView1.model[listView1.currentIndex].surfaceTarget
                                    }
                                    GroupBox {
                                        title:"Surface A"
                                        Column
                                        {
                                            Label
                                            {
                                                text:"Offset: " + listView1.model[listView1.currentIndex].offsetA
                                            }
                                            Label
                                            {
                                                text:"Pitch: " + listView1.model[listView1.currentIndex].pitchA
                                            }
                                        }
                                    }
                                    GroupBox {
                                        title:"Surface B"
                                        Column
                                        {
                                            Label
                                            {
                                                text:"Offset: " + listView1.model[listView1.currentIndex].offsetB
                                            }
                                            Label
                                            {
                                                text:"Pitch: " + listView1.model[listView1.currentIndex].pitchB
                                            }
                                        }
                                    }
                                    GroupBox {
                                        title:"Surface C"
                                        Column
                                        {
                                            Label
                                            {
                                                text:"Offset: " + listView1.model[listView1.currentIndex].offsetC
                                            }
                                            Label
                                            {
                                                text:"Pitch: " + listView1.model[listView1.currentIndex].pitchC
                                            }
                                        }
                                    }
                                    GroupBox {
                                        title:"Surface D"
                                        Column
                                        {
                                            Label
                                            {
                                                text:"Offset: " + listView1.model[listView1.currentIndex].offsetD
                                            }
                                            Label
                                            {
                                                text:"Pitch: " + listView1.model[listView1.currentIndex].pitchD
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    }
}
