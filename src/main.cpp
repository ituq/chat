#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QSplitter>
#include <QListWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include "ChatWindow.h"
#include "ChatBubble.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QMainWindow window;
    window.setWindowTitle("Chat");
    QWidget* central = new QWidget;
    QSplitter *splitter = new QSplitter(Qt::Horizontal);

    QListWidget *leftPanel = new QListWidget();
    leftPanel->addItem("Navigation Item 1");
    leftPanel->addItem("Navigation Item 2");

    ChatWindow *rightPanel = new ChatWindow();

    splitter->addWidget(leftPanel);
    splitter->addWidget(rightPanel);
    splitter->setSizes({384,1536});
    leftPanel->setMinimumWidth(100);
    rightPanel->setMinimumWidth(200);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(splitter);
    layout->setContentsMargins(0, 0, 0, 0);
    central->setLayout(layout);
    window.setCentralWidget(central);


    window.resize(1920,1080);
    window.show();

    return app.exec();
}
