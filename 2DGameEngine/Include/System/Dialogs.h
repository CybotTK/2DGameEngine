#ifndef SYS_DIALOGS_H
#define SYS_DIALOGS_H

#include <string>
#include <vector>

namespace dialogs {
	void ErrorMessage(const std::string& title, const std::string& body);
	void WarningMessage(const std::string& title, const std::string& body);
	bool QuestionMessage(const std::string& title, const std::string& body);

	std::vector<std::string> OpenFile(const std::string& title, std::vector<std::string> filters = { "All files", "*" }, bool multipleSelected = true);
	std::string SaveFile(const std::string& title, std::vector<std::string> filters = { "Save file", "*.gion" });
	std::string SelectFolder(const std::string& title);
}

#endif // !SYS_DIALOGS_H
 
// Source for inspiration :
// https://github.com/samhocevar/portable-file-dialogs