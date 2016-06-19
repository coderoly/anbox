/*
 * Copyright (C) 2016 Simon Fels <morphis@gravedo.de>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranties of
 * MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "anbox/logger.h"
#include "anbox/support/sensors_message_processor.h"

namespace anbox {
namespace support {
SensorsMessageProcessor::SensorsMessageProcessor(const std::shared_ptr<network::SocketMessenger> &messenger) :
    QemudMessageProcessor(messenger) {
}

SensorsMessageProcessor::~SensorsMessageProcessor() {
}

void SensorsMessageProcessor::handle_command(const std::string &command) {
    DEBUG("command %s", command);
    if (command == "list-sensors")
        list_sensors();
}

void SensorsMessageProcessor::list_sensors() {
    // We don't support sensors yet so we mark all as disabled
    int mask = 0;
    char buf[12];
    snprintf(buf, sizeof(buf), "%d", mask);
    send_header(strlen(buf));
    messenger_->send(buf, strlen(buf));
    finish_message();
}
} // namespace support
} // namespace anbox
