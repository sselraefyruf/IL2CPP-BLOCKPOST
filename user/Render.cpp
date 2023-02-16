#include "Render.h"

class PlayerDataArray
{
public:
	char pad_0000[12]; 
	int Count; 
	app::PlayerData* Player[]; 
};

void Visuals::WWE() {
	app::Camera* CurrentCam = (*app::Controll__TypeInfo)->static_fields->csCam;
	if (!CurrentCam) return;

	PlayerDataArray* PlayerDataXD = (PlayerDataArray*)(*app::PLH__TypeInfo)->static_fields->player;
	if (!PlayerDataXD) return;
	
	for (int i = 0; i < PlayerDataXD->Count; ++i) {
		auto Players = PlayerDataXD->Player[i];
		if (!Players) continue;

		app::GameObject* goHeadObj = Players->fields.goHead;
		if (!goHeadObj) continue;

		app::Transform* Transform = app::GameObject_get_transform(goHeadObj, nullptr);
		if (!Transform) continue;

		app::Vector3 EnemyHeadLocation = app::Transform_get_position(Transform, nullptr);

		app::Vector3 screenXD = app::Camera_WorldToScreenPoint(CurrentCam, EnemyHeadLocation, app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr);
		if (screenXD.z <= 1)continue;

		ImVec2 ScreenBottom = { screenXD.x,ImGui::GetIO().DisplaySize.y - screenXD.y };
		ImGui::GetForegroundDrawList()->AddText(ImVec2(ScreenBottom.x, ScreenBottom.y), IM_COL32_WHITE, "PLH_Player");

	}

}