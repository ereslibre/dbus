/*
 * This file is part of the Ideal Library
 * Copyright (C) 2010 Rafael Fernández López <ereslibre@ereslibre.es>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <dbus/dbus.h>

int main(int argc, char ** argv)
{
    DBusError error;
    dbus_error_init(&error);

    DBusConnection *connection = dbus_bus_get(DBUS_BUS_SESSION, &error);
    if (!connection || dbus_error_is_set(&error)) {
        perror("Connection error.");
        exit(1);
    }

    const int ret = dbus_bus_request_name(connection, "test.foo.caller", DBUS_NAME_FLAG_REPLACE_EXISTING, &error);
    if (ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER || dbus_error_is_set(&error)) {
        perror("Ouch.");
        exit(1);
    }

    DBusMessage *const msg = dbus_message_new_method_call("test.foo.bar",
                                                          "/test/foo/Object",
                                                          "test.foo.Roll",
                                                          "Method");

    if (!msg) {
        perror("Ouch.");
        exit(1);
    }

    dbus_uint32_t serial = dbus_message_get_serial(msg);
    dbus_connection_send(connection, msg, &serial);
    dbus_connection_flush(connection);
    dbus_message_unref(msg);

    exit(0);
}
