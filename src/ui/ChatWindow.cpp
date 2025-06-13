#include "ChatWindow.h"
#include <QLabel>
#include <QTimer>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QScrollBar>
#include <QPushButton>

ChatWindow::ChatWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    // Scrollable chat area
    m_scrollArea = new QScrollArea;
    QWidget *chatWidget = new QWidget;
    m_chatLayout = new QVBoxLayout(chatWidget);

    // Important: Add stretch at the end to push messages to top
    m_chatLayout->addStretch();

    m_scrollArea->setWidget(chatWidget);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Input area
    QHBoxLayout *inputLayout = new QHBoxLayout;
    m_messageInput = new QLineEdit;
    QPushButton *sendButton = new QPushButton("Send");

    connect(sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(m_messageInput, &QLineEdit::returnPressed, this, &ChatWindow::sendMessage);

    inputLayout->addWidget(m_messageInput);
    inputLayout->addWidget(sendButton);

    mainLayout->addWidget(m_scrollArea);
    mainLayout->addLayout(inputLayout);
}

void ChatWindow::addMessage(const QString &message, ChatBubble::BubbleType type) {
    ChatBubble *bubble = new ChatBubble(message, type);
    QHBoxLayout *bubbleLayout = new QHBoxLayout;

    if (type == ChatBubble::Sent) {
        bubbleLayout->addStretch();  // Push to right
        bubbleLayout->addWidget(bubble);
    } else {
        bubbleLayout->addWidget(bubble);
        bubbleLayout->addStretch();  // Push to left
    }

    m_chatLayout->addLayout(bubbleLayout);

    // Auto-scroll to show newest message
    QTimer::singleShot(0, this, [this]() {
        m_scrollArea->verticalScrollBar()->setValue(
            m_scrollArea->verticalScrollBar()->maximum()
        );
    });
}

void ChatWindow::sendMessage() {
    QString message = m_messageInput->text().trimmed();
    if (!message.isEmpty()) {
        addMessage(message, ChatBubble::Sent);
        m_messageInput->clear();

        // Simulate received message after a delay
        QTimer::singleShot(1000, this, [this]() {
            addMessage("Thanks for your message!", ChatBubble::Received);
        });
    }
}
