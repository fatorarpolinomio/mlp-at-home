const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const flags = &.{ "-std=c++23", "-Wall", "-Werror" };

    const exe = b.addExecutable(.{
        .name = "mlp",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
        }),
    });

    // 2. Adiciona os arquivos C++
    exe.root_module.addCSourceFiles(.{ 
        .root = b.path("src"), 
        .files = &.{ "main.cpp", "mlp/mlp.cpp", "io/dataIO.cpp" },
        .flags = flags 
    });

    // 3. Linka com a biblioteca padrão do C++
    exe.root_module.linkSystemLibrary("stdc++", .{});

    // 4. Instala o executável
    b.installArtifact(exe);

    // 5. Cria run step
    const run_exe = b.addRunArtifact(exe);
    const run_step = b.step("run", "Run the application");
    run_step.dependOn(&run_exe.step);
}
