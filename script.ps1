param([string] $PROJECT_NAME)
$ROOT_DIR = $PSScriptRoot
$PROJECT_ROOT = Join-Path $ROOT_DIR $PROJECT_NAME
if(Test-Path $PROJECT_ROOT) {
   Write-Host "Project with name $PROJECT_NAME already exists"
}else {
    New-Item -ItemType Directory -Path $PROJECT_ROOT
    $cmakelistsStr = "CMakeLists.txt"
    Set-Location $PROJECT_ROOT 
    New-Item -ItemType Directory -Path include, src
    $include_dir = "$PROJECT_ROOT/include"
    $main_dir = "$Project_root/src"
    New-Item -ItemType File $include_dir/$cmakelistsStr, $PROJECT_ROOT/$cmakelistsStr
    New-Item -ItemType File "$main_dir/main.cpp", $main_dir/$cmakelistsStr
    New-Item -ItemType Directory -Path "$include_dir/hpp", "$include_dir/cpp"
    
  
    $cmake_req = @"
            cmake_minimum_required(VERSION 3.20)
            set(CMAKE_C_COMPILER cl)
            set(CMAKE_CXX_COMPILER cl)
            set(CMAKE_CXX_STANDARD 23)
            project(PackageProj)
            add_subdirectory(include)
            add_subdirectory(src)
"@

$cmake_main_link = @"
            add_executable(main main.cpp)
            target_compile_options(main PRIVATE -Wall)
            target_link_libraries(main PRIVATE )
"@


$cmake_library_create = @"
            add_library()
            target_include_directories( PUBLIC `${CMAKE_CURRENT_SOURCE_DIR}/hpp)
"@


    $cmake_req | Out-File -FilePath $PROJECT_ROOT/$cmakelistsStr
    $cmake_main_link | Out-File -FilePath $main_dir/$cmakelistsStr
    $cmake_library_create | Out-File -FilePath $include_dir/$cmakelistsStr
    
    
    Set-Location $PROJECT_ROOT
    code .
   
}





# Write-Host $PSScriptRoot