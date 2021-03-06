/*
 * QDigiDoc4
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#pragma once

namespace ria {
namespace qdigidoc4 {

enum ContainerState {
    UnsignedContainer       = (1 << 0),
    UnsignedSavedContainer  = (1 << 1),
    SignedContainer         = (1 << 2),

    UnencryptedContainer    = (1 << 3),
    EncryptedContainer      = (1 << 4),
    DecryptedContainer      = (1 << 5)
};

enum Actions {
    AddressAdd,

    CardPhoto,

    ContainerCancel,
    ContainerEncrypt,
    ContainerEmail,
    ContainerLocation,
    ContainerNavigate,
    ContainerSave,

    EncryptContainer,

    FileAdd,
    FileRemove,

    HeadSettings,
    HeadHelp,

    SignatureAdd,
    SignatureRemove
};

enum FileType {
    SignatureContainer,
    CryptoContainer,
    Other
};

enum Pages {
    SignIntro,
    SignDetails,
    CryptoIntro,
    CryptoDetails,
    MyEid
};

}
}
