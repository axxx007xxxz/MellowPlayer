#pragma once

#include "Notifications.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class INotificationPresenter
{
public:
    virtual ~INotificationPresenter() = default;
    virtual void initialize() = 0;
    virtual void display(const Notification& notification) = 0;
};

END_MELLOWPLAYER_NAMESPACE
