#include "ChatBubble.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>

ChatBubble::ChatBubble(const QString &message, BubbleType type, QWidget *parent)
    : QWidget(parent), m_message(message), m_type(type) {
    setupUI();
    setStyleSheet(getBubbleStyle());
}

void ChatBubble::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Message text
    QLabel *messageLabel = new QLabel(m_message);
    messageLabel->setWordWrap(true);
    messageLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

    layout->addWidget(messageLabel);
    layout->setContentsMargins(10, 8, 10, 8);

    // Set maximum width so long messages wrap
    setMaximumWidth(300);
}

QString ChatBubble::getBubbleStyle() {
    if (m_type == Sent) {
        return R"(
            ChatBubble {
                background-color: #0084ff;
                color: white;
                border-radius: 18px;
                margin: 2px;
            }
        )";
    } else {
        return R"(
            ChatBubble {
                background-color: #e4e6ea;
                color: black;
                border-radius: 18px;
                margin: 2px;
            }
        )";
    }
}
