echo off

::from https://stackoverflow.com/questions/39072485/compiling-glsl-to-spir-v-using-premake-5-and-visual-studio-2015
for %%f in (*.vert *.tesc *.tese *.geom *.frag *.comp *.rgen *.rint *.rahit *.rchit *.rmiss *.rcall) do %VULKAN_SDK%\Bin\glslangValidator.exe -V -o .\%%f.spv %%f


pause