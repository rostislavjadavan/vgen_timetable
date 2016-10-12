
#include "TimetableConfig.h"

bool TimetableConfig::load(string filename) {
	try {
		JsonTree jsonTree = JsonTree(loadAsset(filename));

		fontName = jsonTree.hasChild("font") ? jsonTree.getValueForKey<string>("font") : "BebasNeue.ttf";
		fontSize = jsonTree.hasChild("size") ? jsonTree.getValueForKey<int>("size") : 40;
		displayTime = jsonTree.hasChild("displayTime") ? jsonTree.getValueForKey<int>("displayTime") : 30;
		intervalTime = jsonTree.hasChild("intervalTime") ? jsonTree.getValueForKey<int>("intervalTime") : 600;

		if (jsonTree.hasChild("djs")) {
			for (const auto &dj : jsonTree["djs"]) {
				ConfigDj configDj;

				configDj.name = dj.hasChild("name") ? dj.getValueForKey<string>("name") : "unknown";
				configDj.timeFrom = dj.hasChild("from") ? dj.getValueForKey<string>("from") : "";
				configDj.timeTo = dj.hasChild("to") ? dj.getValueForKey<string>("to") : "";
				configDj.fontSize = dj.hasChild("size") ? dj.getValueForKey<int>("size") : fontSize;

				djs.push_back(configDj);
			}
		}
	}
	catch (JsonTree::ExcJsonParserError e) {
		return false;
	}
	catch (AssetLoadExc) {
		return false;
	}
	return true;
}

ConfigDj TimetableConfig::findDjByTime(int time)
{
	for (ConfigDj dj : this->djs) {
		if (time > dj.getTimeFrom() && time < dj.getTimeTo()) {
			return dj;
		}
	}

	return ConfigDj();
}
