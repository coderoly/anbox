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
#include "anbox/support/camera_message_processor.h"

namespace anbox {
namespace support {
CameraMessageProcessor::CameraMessageProcessor(const std::shared_ptr<network::SocketMessenger> &messenger) :
    messenger_(messenger) {
}

CameraMessageProcessor::~CameraMessageProcessor() {
}

bool CameraMessageProcessor::process_data(const std::vector<std::uint8_t> &data) {
    DEBUG("Received: %s", utils::hex_dump(data.data(), data.size()));

    for (const auto &byte : data)
        buffer_.push_back(byte);

    process_commands();

    return true;
}

void CameraMessageProcessor::process_commands() {
    while (true) {
        size_t size;
        for (size = 0; size < buffer_.size(); size++) {
            if (buffer_.at(size) == 0x0)
                break;
        }

        std::string command;
        command.insert(0, reinterpret_cast<const char*>(buffer_.data()), size);
        buffer_.erase(buffer_.begin(), buffer_.begin() + size);

        handle_command(command);
    }
}

void CameraMessageProcessor::handle_command(const std::string &command) {
    if (command == "list")
        list();
}

void CameraMessageProcessor::list() {
    char buf[5];
    snprintf(buf, 5, "\n");
    messenger_->send(buf, strlen(buf));
}
} // namespace support
} // namespace anbox
