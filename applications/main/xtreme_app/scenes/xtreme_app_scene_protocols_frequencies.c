#include "../xtreme_app.h"

enum VarItemListIndex {
    VarItemListIndexStaticFrequency,
    VarItemListIndexHopperFrequency,
};

void xtreme_app_scene_protocols_frequencies_var_item_list_callback(void* context, uint32_t index) {
    XtremeApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

static void xtreme_app_scene_protocols_frequencies_static_frequency_changed(VariableItem* item) {
    XtremeApp* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    uint32_t value = *FrequencyList_get(app->subghz_static_frequencies, index);
    char text[10] = {0};
    snprintf(text, sizeof(text), "%lu.%02lu", value / 1000000, (value % 1000000) / 10000);
    variable_item_set_current_value_text(item, text);
}

static void xtreme_app_scene_protocols_frequencies_hopper_frequency_changed(VariableItem* item) {
    XtremeApp* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    uint32_t value = *FrequencyList_get(app->subghz_hopper_frequencies, index);
    char text[10] = {0};
    snprintf(text, sizeof(text), "%lu.%02lu", value / 1000000, (value % 1000000) / 10000);
    variable_item_set_current_value_text(item, text);
}

void xtreme_app_scene_protocols_frequencies_on_enter(void* context) {
    XtremeApp* app = context;
    VariableItemList* var_item_list = app->var_item_list;
    VariableItem* item;

    item = variable_item_list_add(var_item_list, "Static Freq", FrequencyList_size(app->subghz_static_frequencies), xtreme_app_scene_protocols_frequencies_static_frequency_changed, app);
    variable_item_set_current_value_index(item, 0);
    if(FrequencyList_size(app->subghz_static_frequencies)) {
        uint32_t value = *FrequencyList_get(app->subghz_static_frequencies, 0);
        char text[10] = {0};
        snprintf(text, sizeof(text), "%lu.%02lu", value / 1000000, (value % 1000000) / 10000);
        variable_item_set_current_value_text(item, text);
    } else {
        variable_item_set_current_value_text(item, "None");
    }

    item = variable_item_list_add(var_item_list, "Hopper Freq", FrequencyList_size(app->subghz_hopper_frequencies), xtreme_app_scene_protocols_frequencies_hopper_frequency_changed, app);
    variable_item_set_current_value_index(item, 0);
    if(FrequencyList_size(app->subghz_hopper_frequencies)) {
        uint32_t value = *FrequencyList_get(app->subghz_hopper_frequencies, 0);
        char text[10] = {0};
        snprintf(text, sizeof(text), "%lu.%02lu", value / 1000000, (value % 1000000) / 10000);
        variable_item_set_current_value_text(item, text);
    } else {
        variable_item_set_current_value_text(item, "None");
    }

    variable_item_list_set_enter_callback(
        var_item_list, xtreme_app_scene_protocols_frequencies_var_item_list_callback, app);

    variable_item_list_set_selected_item(
        var_item_list, scene_manager_get_scene_state(app->scene_manager, XtremeAppSceneProtocolsFrequencies));

    view_dispatcher_switch_to_view(app->view_dispatcher, XtremeAppViewVarItemList);
}

bool xtreme_app_scene_protocols_frequencies_on_event(void* context, SceneManagerEvent event) {
    XtremeApp* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        scene_manager_set_scene_state(app->scene_manager, XtremeAppSceneProtocolsFrequencies, event.event);
        consumed = true;
        switch(event.event) {
        default:
            break;
        }
    }

    return consumed;
}

void xtreme_app_scene_protocols_frequencies_on_exit(void* context) {
    XtremeApp* app = context;
    variable_item_list_reset(app->var_item_list);
}