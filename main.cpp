#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::filesystem::exists;
using std::filesystem::current_path;
using std::filesystem::copy_file;
using std::filesystem::copy_options::overwrite_existing;
using std::filesystem::path;
using std::filesystem::directory_iterator;
using std::filesystem::is_directory;
using std::filesystem::is_regular_file;
using std::string;
using std::to_string;
using std::vector;

enum class Dir
{
    none,
    browser,
    hub,
    compiler,
    engineAndGame
};

static vector<string> GetAllReleaseDLLs()
{
    cout << "\n==================================================\n\n";

    string dllPath = path(current_path()).string();
    vector<string> releaseVector{};
    for (const auto& dllFolder : directory_iterator(dllPath))
    {
        if (is_directory(dllFolder))
        {
            for (const auto& dllSubFolder : directory_iterator(dllFolder))
            {
                if (is_directory(dllSubFolder)
                    && path(dllSubFolder).stem().string() == "release")
                {
                    for (const auto& releaseDLL : directory_iterator(dllSubFolder))
                    {
                        if (is_regular_file(releaseDLL)
                            && path(releaseDLL).extension().string() == ".dll")
                        {
                            string releaseDLLStr = path(releaseDLL).string();
                            cout << "Found release DLL '" << path(releaseDLLStr).filename().string() << "'!\n";
                            releaseVector.push_back(releaseDLLStr);
                        }
                    }
                }
            }
        }
    }

    string dllPathStem = path(dllPath).parent_path().stem().string();
    if (releaseVector.size() == 0)
    {
        cout << "\nError: Failed to find any releases DLLs from '" << dllPathStem << "'!\n\n";
        return releaseVector;
    }
    else
    {
        cout << "\nFound '" << to_string(releaseVector.size()) << "' release dlls from '" << dllPathStem << "'!\n\n";
        return releaseVector;
    }
}
static vector<string> GetAllDebugDLLs()
{
    cout << "\n==================================================\n\n";

    string dllPath = path(current_path()).string();
    vector<string> debugVector{};
    for (const auto& dllFolder : directory_iterator(dllPath))
    {
        if (is_directory(dllFolder))
        {
            for (const auto& dllSubFolder : directory_iterator(dllFolder))
            {
                if (is_directory(dllSubFolder)
                    && path(dllSubFolder).stem().string() == "debug")
                {
                    for (const auto& debugDLL : directory_iterator(dllSubFolder))
                    {
                        if (is_regular_file(debugDLL)
                            && path(debugDLL).extension().string() == ".dll")
                        {
                            string debugDLLStr = path(debugDLL).string();
                            cout << "Found debug DLL '" << path(debugDLLStr).filename().string() << "'!\n";
                            debugVector.push_back(debugDLLStr);
                        }
                    }
                }
            }
        }
    }

    string dllPathStem = path(dllPath).parent_path().stem().string();
    if (debugVector.size() == 0)
    {
        cout << "\nError: Failed to find any debug DLLs from '" << dllPathStem << "'!\n\n";
        return debugVector;
    }
    else
    {
        cout << "\nFound '" << to_string(debugVector.size()) << "' debug dlls from '" << dllPathStem << "'!\n\n";
        return debugVector;
    }
}

static bool CopyToTarget(const vector<string>& originVector, const string& targetFolder)
{
    if (!exists(targetFolder))
    {
        cout << "Error: Target folder path '" << targetFolder << "' does not exist! Cannot copy file to target.\n";
        return false;
    }

    for (const auto& file : originVector)
    {
        string origin = path(file).string();
        string target = (path(targetFolder) / path(origin).filename()).string();

        copy_file(origin, target, overwrite_existing);

        cout << "Copied '" << path(origin).filename().string() << "' to '" << path(targetFolder).stem().string() << "!\n";
    }

    return true;
}

static void Invalid()
{
    cout << "Error: '" << (current_path()).string() << "' is an invalid path for this program!\n";
}

static void CopyToBrowser()
{
    cout << "Currently inside of 'Elypso browser'!\n";

    vector<string> releaseDLLs = GetAllReleaseDLLs();
    string releaseFolder = (current_path().parent_path() / "files" / "external dlls" / "release").string();
    CopyToTarget(releaseDLLs, releaseFolder);

    vector<string> debugDLLs = GetAllDebugDLLs();
    string debugFolder = (current_path().parent_path() / "files" / "external dlls" / "debug").string();
    CopyToTarget(debugDLLs, debugFolder);
}

static void CopyToHub()
{
    cout << "Currently inside of 'Elypso hub'!\n";

    vector<string> releaseDLLs = GetAllReleaseDLLs();
    string releaseFolder = (current_path().parent_path() / "files" / "external dlls" / "release").string();
    CopyToTarget(releaseDLLs, releaseFolder);

    vector<string> debugDLLs = GetAllDebugDLLs();
    string debugFolder = (current_path().parent_path() / "files" / "external dlls" / "debug").string();
    CopyToTarget(debugDLLs, debugFolder);
}

static void CopyToCompiler()
{
    cout << "Currently inside of 'Elypso compiler'!\n";

    vector<string> releaseDLLs = GetAllReleaseDLLs();
    string releaseFolder = (current_path().parent_path() / "files" / "external dlls" / "release").string();
    CopyToTarget(releaseDLLs, releaseFolder);

    vector<string> debugDLLs = GetAllDebugDLLs();
    string debugFolder = (current_path().parent_path() / "files" / "external dlls" / "debug").string();
    CopyToTarget(debugDLLs, debugFolder);
}

static void CopyToEngineAndGame()
{
    cout << "Currently inside of 'Elypso engine' and 'Game template'!\n";

    vector<string> releaseDLLs = GetAllReleaseDLLs();
    string engineReleaseFolder = (current_path().parent_path() / "Engine" / "files" / "external dlls" / "release").string();
    CopyToTarget(releaseDLLs, engineReleaseFolder);
    string gameReleaseFolder = (current_path().parent_path() / "Game" / "files" / "external dlls" / "release").string();
    CopyToTarget(releaseDLLs, gameReleaseFolder);

    vector<string> debugDLLs = GetAllDebugDLLs();
    string engineDebugFolder = (current_path().parent_path() / "Engine" / "files" / "external dlls" / "debug").string();
    CopyToTarget(debugDLLs, engineDebugFolder);
    string gameDebugFolder = (current_path().parent_path() / "Game" / "files" / "external dlls" / "debug").string();
    CopyToTarget(debugDLLs, gameDebugFolder);
}

int main()
{
    cout << "Initializing DLL copy!\n";
    cout << "\n==================================================\n\n";

    string currentDir = current_path().parent_path().stem().string();

    Dir dir{};
    if (currentDir == "Elypso-browser") dir = Dir::browser;
    if (currentDir == "Elypso-hub") dir = Dir::hub;
    if (currentDir == "Elypso-compiler") dir = Dir::compiler;
    if (currentDir == "Elypso-engine") dir = Dir::engineAndGame;

    switch (dir)
    {
    default:
        Invalid();
        break;
    case Dir::browser:
        CopyToBrowser();
        break;
    case Dir::hub:
        CopyToHub();
        break;
    case Dir::compiler:
        CopyToCompiler();
        break;
    case Dir::engineAndGame:
        CopyToEngineAndGame();
        break;
    }

    cout << "\n==================================================\n\n";
    cout << "Press Enter to shut down...\n";

    cin.get();
    return 0;
}