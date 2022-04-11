# windows:
# INCLUDE_DIRECTORIES("C:\\Program Files\\Java\\jdk-13.0.1\\include")
# INCLUDE_DIRECTORIES("C:\\Program Files\\Java\\jdk-13.0.1\\include\\win32")

# macOS:
INCLUDE_DIRECTORIES("/Library/Java/JavaVirtualMachines/openjdk.jdk/Contents/Home/include")
INCLUDE_DIRECTORIES("/Library/Java/JavaVirtualMachines/openjdk.jdk/Contents/Home/include/darwin")

# linux:
INCLUDE_DIRECTORIES("~/.sdkman/candidates/java/current/include")
INCLUDE_DIRECTORIES("~/.sdkman/candidates/java/current/include/linux")

INCLUDE_DIRECTORIES("./jni")
INCLUDE_DIRECTORIES("./utils")
INCLUDE_DIRECTORIES("./game")
INCLUDE_DIRECTORIES("./game/physics")
INCLUDE_DIRECTORIES("./game/tasks")
INCLUDE_DIRECTORIES("./msg")

# add_subdirectory("./libs/bullet3")

INCLUDE_DIRECTORIES("./libs/bullet3/src")
INCLUDE_DIRECTORIES("./libs/json")

