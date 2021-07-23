import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.4

import Translator 1.0
import FileInput 1.0
import FileOutput 1.0

Window {
    id: root

    function swapLanguages() {
        _textTranslator.changeCurrentMode()
        if (topLanguage.text === "Morse") {
            topLanguage.text = "English"
            bottomLanguage.text = "Morse"
        } else {
            topLanguage.text = "Morse"
            bottomLanguage.text = "English"
        }
        bottomText.text = topText.text
    }

    width: 480
    height: 640
    visible: true
    title: qsTr("Morse Translator")

    // Rectangle for translated text
    Rectangle {
        id: topRectangle

        color: "#609AE0"
        width: root.width
        height: root.height * 0.38
        radius: 10

        // This rectangle is used just for deleting top-radius of topRectangle.
        Rectangle {
            anchors {
                top: topRectangle.top
                left: topRectangle.left
                right: topRectangle.right
            }
            color: topRectangle.color
            height: topRectangle.radius
        }

        // Text field that contains language of top rectangle.
        Text {
            id: topLanguage
            anchors {
                top: parent.top
                left: parent.left
                leftMargin: 20
                topMargin: 10
            }

            text: "Morse"
            color: "white"
            font {
                pointSize: 14
            }
        }

        // TextArea with translated text
        ScrollView {
            anchors {
                topMargin: 5
                leftMargin: 10
                left: parent.left
                top: topLanguage.bottom
            }

            width: parent.width - 20
            height: parent.height - 50
            clip: true

            TextArea {
                id: topText

                placeholderText: qsTr(
                                     "Translation of your text will be here...")
                height: parent.height
                width: parent.width
                background: Rectangle {
                    color: topRectangle.color
                }
                color: "white"
                font {
                    pointSize: 18
                }
                readOnly: true
                selectByKeyboard: true
                selectByMouse: true
                wrapMode: TextEdit.WordWrap
            }
        }
    }
    // Rectangle for entering text.
    Rectangle {
        id: bottomRectangle
        anchors.top: topRectangle.bottom

        width: root.width
        height: root.height * 0.62
        color: "white"

        // Text field that contains language of bottom rectangle.
        Text {
            id: bottomLanguage
            anchors {
                top: parent.top
                left: parent.left
                leftMargin: 20
                topMargin: 10
            }

            text: "English"
            color: "black"
            font {
                pointSize: 14
            }
        }
        // TextArea with entering text.
        ScrollView {
            anchors {
                topMargin: 5
                leftMargin: 10
                left: parent.left
                top: bottomLanguage.bottom
            }

            height: parent.height - 100
            width: parent.width - 20
            clip: true
            TextArea {
                id: bottomText

                placeholderText: qsTr("Enter text...")
                height: parent.height
                width: parent.width
                font {
                    pointSize: 18
                }
                selectByKeyboard: true
                selectByMouse: true
                wrapMode: TextEdit.Wrap

                onTextChanged: {
                    _textTranslator.parseText(bottomText.text)
                    topText.text = _textTranslator.translateText()
                    var isError = topText.text === _textTranslator.getErrorMessage()
                    if (isError) {
                        topRectangle.color = "#BF3030" // RED
                    } else {
                        topRectangle.color = "#609AE0" // BLUE
                    }
                }
            }
        }

        // Button for swaping languages.
        MouseArea {
            id: swappingButton
            anchors {
                left: parent.left
                bottom: parent.bottom
                leftMargin: 5
                bottomMargin: 5
            }

            width: 50
            height: 50
            cursorShape: Qt.PointingHandCursor

            onClicked: {
                var isError = _textTranslator.getErrorMessage() === topText.text;
                if (!isError) {
                    swapLanguages()
                }
            }
            Image {
                anchors.centerIn: parent
                source: "images/swap"
                sourceSize.width: 30
                sourceSize.height: 30
            }
        }

        // Button for reading text from file.
        MouseArea {
            id: inputButton
            anchors {
                left: swappingButton.right
                bottom: parent.bottom
                bottomMargin: 5
            }

            width: 50
            height: 50
            cursorShape: Qt.PointingHandCursor

            onClicked: {
                var text = _fileInput.readFromFile()
                if (text !== "__CANCELED") {
                    if (_textTranslator.getTextLanguage() !==
                            _textTranslator.guessLanguage(text)) {
                        swapLanguages()
                    }
                    bottomText.text = text
                }
            }

            Image {
                anchors.centerIn: parent
                source: "images/input"
                sourceSize.width: 30
                sourceSize.height: 30
            }
        }

        // Button for writing translated text to file
        MouseArea {
            id: outputButton
            anchors {
                left: inputButton.right
                bottom: parent.bottom
                bottomMargin: 5
            }

            cursorShape: Qt.PointingHandCursor
            width: 50
            height: 50

            onClicked: {
                _fileOutput.writeToFile(topText.text)
            }

            Image {
                anchors.centerIn: parent
                source: "images/output"
                sourceSize.width: 30
                sourceSize.height: 30
            }
        }
    }

    Translator_qml {
        id: _textTranslator
    }
    FileInput_qml {
        id: _fileInput
    }
    FileOutput_qml {
        id: _fileOutput
    }
}
