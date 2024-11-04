#include "uuidgenorator.h"

#include <QDebug>
#include <QClipboard>
#include <QGuiApplication>
UUIDGenorator::UUIDGenorator(QObject *parent)
    : QObject{parent}
{
}

QString UUIDGenorator::generateUuid(){
    setUUID(QUuid::createUuid().toString(QUuid::WithoutBraces));
    QGuiApplication::clipboard()->setText(m_UUID);
    return m_UUID;
}

void UUIDGenorator::requestFocus()
{
    emit focus();
}

QString UUIDGenorator::UUID() const
{
    return m_UUID;
}

void UUIDGenorator::setUUID(const QString &newUUID)
{
    if (m_UUID == newUUID)
        return;
    m_UUID = newUUID;
    emit UUIDChanged();
}
