#pragma once
enum class SceneIds
{
	None = -1, //유효한 씬 ID들과 구분
	Title,
	Game,
	Ending,
};

enum class SortingLayers
{
	Background,
	Foreground,
	Default,
	UI,
};