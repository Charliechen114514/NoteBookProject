# Android学习小记3

## Gradle构建脚本分析

​	项目不知道怎么构建的！这个事情是一个非常危险的事情，我们来看看这一长串构建脚本

```
plugins {
    alias(libs.plugins.android.application)
    alias(libs.plugins.jetbrains.kotlin.android)
}

android {
    namespace = "com.example.demoofmyfirstapplication"
    compileSdk = 34

    defaultConfig {
        applicationId = "com.example.demoofmyfirstapplication"
        minSdk = 24
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        vectorDrawables {
            useSupportLibrary = true
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    kotlinOptions {
        jvmTarget = "1.8"
    }
    buildFeatures {
        compose = true
    }
    composeOptions {
        kotlinCompilerExtensionVersion = "1.5.1"
    }
    packaging {
        resources {
            excludes += "/META-INF/{AL2.0,LGPL2.1}"
        }
    }
}

dependencies {

    implementation(libs.androidx.core.ktx)
    implementation(libs.androidx.lifecycle.runtime.ktx)
    implementation(libs.androidx.activity.compose)
    implementation(platform(libs.androidx.compose.bom))
    implementation(libs.androidx.ui)
    implementation(libs.androidx.ui.graphics)
    implementation(libs.androidx.ui.tooling.preview)
    implementation(libs.androidx.material3)
    testImplementation(libs.junit)
    androidTestImplementation(libs.androidx.junit)
    androidTestImplementation(libs.androidx.espresso.core)
    androidTestImplementation(platform(libs.androidx.compose.bom))
    androidTestImplementation(libs.androidx.ui.test.junit4)
    debugImplementation(libs.androidx.ui.tooling)
    debugImplementation(libs.androidx.ui.test.manifest)
}
```





### 主要部分解析

#### 1. **插件配置**

```
plugins {
    alias(libs.plugins.android.application)
    alias(libs.plugins.jetbrains.kotlin.android)
}
```

- `alias(libs.plugins.android.application)`：应用 Android 插件，用于构建 Android 应用。
- `alias(libs.plugins.jetbrains.kotlin.android)`：应用 Kotlin 插件，用于支持 Kotlin 编程语言和 Android 开发。

这些插件分别用于处理 Android 应用构建和 Kotlin 的 Android 集成。

#### 2. **Android 配置**

```
android {
    namespace = "com.example.demoofmyfirstapplication"
    compileSdk = 34

    defaultConfig {
        applicationId = "com.example.demoofmyfirstapplication"
        minSdk = 24
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        vectorDrawables {
            useSupportLibrary = true
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }

    kotlinOptions {
        jvmTarget = "1.8"
    }

    buildFeatures {
        compose = true
    }

    composeOptions {
        kotlinCompilerExtensionVersion = "1.5.1"
    }

    packaging {
        resources {
            excludes += "/META-INF/{AL2.0,LGPL2.1}"
        }
    }
}
```

- **`namespace`**：定义应用的命名空间，通常是应用包名，指明了应用的唯一标识符。
- **`compileSdk`**：指定编译 SDK 版本。此处使用的是 **SDK 34**。
- **`defaultConfig`**：
  - **`applicationId`**：应用的唯一标识符。
  - **`minSdk`**：应用支持的最低 Android 版本，设置为 24（Android 7.0）。
  - **`targetSdk`**：目标 SDK 版本，设置为 34（最新的 Android 版本）。
  - **`versionCode`** 和 **`versionName`**：分别设置版本号和版本名称，用于版本管理。
  - **`testInstrumentationRunner`**：指定测试运行器，这里是 AndroidJUnitRunner。
  - **`vectorDrawables`**：启用支持库，使得可以使用矢量图资源（如 SVG 格式）在所有设备上显示。
- **`buildTypes`**：配置不同的构建类型。在这里配置了 **release** 构建类型，禁用了 ProGuard 的代码混淆（`isMinifyEnabled = false`），并且提供了默认的 `proguard-android-optimize.txt` 和自定义的 `proguard-rules.pro` 文件。
- **`compileOptions`**：指定编译时的 Java 版本兼容性，设置为 **Java 1.8**。
- **`kotlinOptions`**：设置 Kotlin 编译时的目标 JVM 版本为 **1.8**。
- **`buildFeatures`**：启用 Jetpack Compose 功能。
  - `compose = true`：启用 Jetpack Compose 用于构建 UI。
- **`composeOptions`**：设置 Jetpack Compose 编译器扩展版本，此处设置为 **1.5.1**。
- **`packaging`**：配置打包时的资源排除规则。
  - `excludes += "/META-INF/{AL2.0,LGPL2.1}"`：从打包中排除这些许可证文件，通常这是为了避免不必要的冲突或冗余文件。

#### 3. **依赖管理**

```
dependencies {
    implementation(libs.androidx.core.ktx)
    implementation(libs.androidx.lifecycle.runtime.ktx)
    implementation(libs.androidx.activity.compose)
    implementation(platform(libs.androidx.compose.bom))
    implementation(libs.androidx.ui)
    implementation(libs.androidx.ui.graphics)
    implementation(libs.androidx.ui.tooling.preview)
    implementation(libs.androidx.material3)
    testImplementation(libs.junit)
    androidTestImplementation(libs.androidx.junit)
    androidTestImplementation(libs.androidx.espresso.core)
    androidTestImplementation(platform(libs.androidx.compose.bom))
    androidTestImplementation(libs.androidx.ui.test.junit4)
    debugImplementation(libs.androidx.ui.tooling)
    debugImplementation(libs.androidx.ui.test.manifest)
}
```

- `implementation`

  ：定义应用的常规依赖，例如：

  - **`libs.androidx.core.ktx`**：包含 AndroidX 核心库的 Kotlin 扩展。
  - **`libs.androidx.lifecycle.runtime.ktx`**：包含生命周期的 Kotlin 扩展库。
  - **`libs.androidx.activity.compose`**：支持 Jetpack Compose 的 Activity 扩展。
  - **`libs.androidx.ui`**、**`libs.androidx.ui.graphics`** 等：与 Jetpack Compose 相关的库，用于构建 UI、处理图形等。
  - **`libs.androidx.material3`**：Material Design 3 组件库，用于实现现代的 UI 设计。

- `testImplementation`

  ：包含测试相关的依赖，如 JUnit。

  - **`libs.junit`**：JUnit 测试库，用于单元测试。

- `androidTestImplementation`

  ：包含 Android 测试相关的依赖，用于 UI 测试、集成测试等：

  - **`libs.androidx.junit`**：AndroidX JUnit 测试库。
  - **`libs.androidx.espresso.core`**：Espresso 测试库，用于 UI 测试。
  - **`libs.androidx.ui.test.junit4`**：Jetpack Compose 的 JUnit4 测试扩展。

- `debugImplementation`

  ：仅在调试模式下使用的库，例如用于调试 UI：

  - **`libs.androidx.ui.tooling`**：用于调试 Jetpack Compose UI。
  - **`libs.androidx.ui.test.manifest`**：与 UI 测试相关的工具，确保测试代码的正确性。

​	完事.