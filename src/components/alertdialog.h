#pragma once

#include "nlohmann/json_fwd.hpp"

namespace ImModernUI {
    /*
    {
        "lable": "alert dialog",
        "title": "Are you absolutely sure?", 
        "description": "This action cannot be undone. This will permanently delete your account and remove your data from our servers.",
        "cancel": "Cancel", 
        "action": "Continue"
    }
    */
    bool AlertDialog(
        const nlohmann::json& attr, 
        bool * open
    );

    void ShowAlertDialogExamples();
}