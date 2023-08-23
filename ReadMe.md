# Between

# What is Between?

I want to create a render engine that can both run on Windows and Mac.

# How to create a test project

You can create a new folder and put the test code in it. Then in the CmakeLists.txt in root folder, using `add_subdirectory(yourNewFolder)` to add it in the base project. 

Then in the folder, you can copy the CmakeLists.txt in test folder into it, then using cmake command to regenerate the project. At last you can get a new project in the generated sln.

# Reference

Till Now(2023.08.22). This project is mostly depending on `https://github.com/gukazma/learnopengl.git`