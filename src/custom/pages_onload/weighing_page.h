#include <Arduino.h>
#include "../../ui/ui.h"

void weighingPage_init(DynamicJsonDocument& rpi_doc) {
    String details = rpi_doc["details"];

    if (details != "null") {
        JsonObject detailsObj = rpi_doc["details"].as<JsonObject>();
        String product = detailsObj["product"].as<String>();
        String lot = detailsObj["lot"].as<String>();
        String balanceID = detailsObj["balanceID"].as<String>();
        String tabletID = detailsObj["tabletID"].as<String>();
        String mean_weight = detailsObj["mean_weight"].as<String>();
        String percent_weight = detailsObj["percent_weight"].as<String>();
        String weight_inhouse_min = detailsObj["weight_inhouse_min"].as<String>();
        String weight_inhouse_max = detailsObj["weight_inhouse_max"].as<String>();
        String weight_reg_min = detailsObj["weight_reg_min"].as<String>();
        String weight_reg_max = detailsObj["weight_reg_max"].as<String>();
        String thickness_min = detailsObj["thickness_min"].as<String>();
        String thickness_max = detailsObj["thickness_max"].as<String>();

        lv_label_set_text(ui_ProductName, product.c_str());
        lv_label_set_text(ui_LotNumber, lot.c_str());
        lv_label_set_text(ui_BalanceID, balanceID.c_str());
        lv_label_set_text(ui_TabletID, tabletID.c_str());
        lv_label_set_text(ui_Weight10s, mean_weight.c_str());
        lv_label_set_text(ui_Weight10sPer, percent_weight.c_str());
        lv_label_set_text(ui_WeightInhouseMin, weight_inhouse_min.c_str());
        lv_label_set_text(ui_WeightInhouseMax, weight_inhouse_max.c_str());
        lv_label_set_text(ui_WeightRegMin, weight_reg_min.c_str());
        lv_label_set_text(ui_WeightRegMax, weight_reg_max.c_str());
        lv_label_set_text(ui_ThicknessMin, thickness_min.c_str());
        lv_label_set_text(ui_ThicknessMax, thickness_max.c_str());
    }
}