#ifndef SYS_DIALOGS_H
#define SYS_DIALOGS_H

#include <string>
#include <vector>

namespace dialogs {
	std::vector<std::string> OpenFile(const std::string& title, std::vector<std::string> filters = { "All files", "*" }, bool multipleSelected = true);
}

#endif // !SYS_DIALOGS_H
