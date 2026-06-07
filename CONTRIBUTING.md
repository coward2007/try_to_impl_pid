# 贡献指南

欢迎为 **try_to_impl_pid** 项目做出贡献！本文档将引导你完成从 Fork 到提交 Pull Request 的完整流程。

---

## 目录

- [1. Fork 仓库](#1-fork-仓库)
- [2. Clone 到本地](#2-clone-到本地)
- [3. 本地开发与修改](#3-本地开发与修改)
- [4. 提交 Pull Request](#4-提交-pull-request)
- [5. 常见问题](#5-常见问题)

---

## 1. Fork 仓库

Fork 是将原仓库复制到你自己的 GitHub 账户下，这样你就可以自由修改而不影响原仓库。

### 步骤：

1. **登录 GitHub**  
   在浏览器中打开 [GitHub](https://github.com) 并登录你的账号。如果没有账号，请先[注册](https://github.com/signup)。

2. **访问原仓库**  
   打开原仓库地址：[https://github.com/vex-crepe/try_to_impl_pid](https://github.com/vex-crepe/try_to_impl_pid)

3. **点击 Fork 按钮**  
   在页面右上角，点击 **Fork** 按钮（分叉图标）。

4. **选择目标账户**  
   在弹出的对话框中，选择你自己的 GitHub 账户作为 Fork 的目标。等待几秒钟，GitHub 会自动完成 Fork。

5. **确认 Fork 成功**  
   Fork 完成后，浏览器会跳转到你的 Fork 仓库，地址格式为：
   ```
   https://github.com/<你的用户名>/try_to_impl_pid
   ```

> 📌 **提示**：Fork 后的仓库与原仓库是独立的，你可以自由修改而不会影响原仓库。

---

## 2. Clone 到本地

Fork 完成后，你需要将远程仓库克隆到本地计算机进行开发。

### 步骤：

1. **复制仓库地址**  
   在你的 Fork 仓库页面中，点击绿色的 **Code** 按钮，复制 HTTPS 或 SSH 地址：
   ```
   # HTTPS 格式（推荐）
   https://github.com/<你的用户名>/try_to_impl_pid.git

   # SSH 格式（需要配置 SSH Key）
   git@github.com:<你的用户名>/try_to_impl_pid.git
   ```

2. **打开终端**  
   在 Windows 上可以使用 Git Bash、PowerShell 或命令提示符；macOS/Linux 使用终端。

3. **执行 Clone 命令**  
   ```bash
   # 进入你想存放项目的目录
   cd ~/Documents

   # 克隆仓库（将 <你的用户名> 替换为你的 GitHub 用户名）
   git clone https://github.com/<你的用户名>/try_to_impl_pid.git
   ```

4. **进入项目目录**  
   ```bash
   cd try_to_impl_pid
   ```

5. **添加上游仓库（Upstream）**  
   添加上游仓库可以方便地同步原仓库的更新：
   ```bash
   git remote add upstream https://github.com/vex-crepe/try_to_impl_pid.git
   ```

6. **验证远程仓库配置**  
   ```bash
   git remote -v
   ```
   输出应类似：
   ```
   origin    https://github.com/<你的用户名>/try_to_impl_pid.git (fetch)
   origin    https://github.com/<你的用户名>/try_to_impl_pid.git (push)
   upstream  https://github.com/vex-crepe/try_to_impl_pid.git (fetch)
   upstream  https://github.com/vex-crepe/try_to_impl_pid.git (push)
   ```

7. **拉取子模块（如果有的话）**  
   ```bash
   git submodule update --init --recursive
   ```

---

## 3. 本地开发与修改

现在你可以在本地进行代码修改了。

### 步骤：

1. **创建新分支**  
   为你的修改创建一个独立的分支，保持 `main` 分支干净。

   > ⚠️ **分支命名规范**：分支名由 **你名字的首字母** + `_pid` 构成。

2. **进行代码修改**  
   根据项目需求修改代码。本项目需要你：
   - 实现 [src/pid.cpp](src/pid.cpp) 中的 `PID::update` 函数
   - 在 [src/main.cpp](src/main.cpp) 中调优 `cfg` 对象的 PID 参数

3. **编译与测试**  
   本项目使用 g++ 直接编译，双击运行生成的 `main.exe` 即可。

   **方法一：使用 VSCode 任务（推荐）**
   在 VSCode 中打开 `src/` 目录下的任意源文件，按 `Ctrl+Shift+B` 触发默认构建任务，自动编译 `main.cpp` + `pid.cpp` 并生成 `main.exe`。

   **方法二：手动命令行**
   ```bash
   # 进入 src 目录
   cd src

   # 编译并链接所有源文件
   g++ -g main.cpp pid.cpp -o main.exe

   # 运行程序
   ./main.exe
   ```
   运行后会生成一个可视化 HTML 文件，用于检查你的实现与调参是否正确。

4. **查看修改状态**  
   ```bash
   git status
   ```

5. **暂存修改**  
   ```bash
   # 添加特定文件
   git add src/pid.cpp

   # 或添加所有修改
   git add .
   ```

6. **提交修改**  
   ```bash
   git commit -m "实现 PID update 函数并调优参数"
   ```

7. **推送到你的 Fork 仓库**  
   ```bash
   git push origin <你的分支名>
   ```

---

## 4. 提交 Pull Request

当你完成修改并推送到你的 Fork 仓库后，可以提交 Pull Request（PR）请求原仓库合并你的代码。

### 步骤：

1. **打开你的 Fork 仓库**  
   在浏览器中访问 `https://github.com/<你的用户名>/try_to_impl_pid`

2. **发起 Pull Request**  
   你会在页面上看到一个黄色的提示条 **"This branch is X commits ahead of vex-crepe:main"**，点击旁边的 **Contribute** 按钮，然后点击 **Open Pull Request**。

   或者直接点击 **Pull requests** 选项卡 → **New pull request**。

3. **选择分支**  
   - **base repository**：`vex-crepe/try_to_impl_pid`，**base**：`main`（目标分支）  
   - **head repository**：`<你的用户名>/try_to_impl_pid`，**compare**：`<你的分支名>`

4. **填写 PR 信息**  
   - **标题**：简洁明了地描述你的修改（如 "实现 PID update 函数"）
   - **描述**：详细说明：
     ```
     ## 修改内容
     - 实现了 pid.cpp 中的 update 函数
     - 调整了 main.cpp 中的 PID 参数

     ## 测试结果
     - 可视化的 HTML 输出正确，系统响应符合预期

     ## 截图（如有）
     ```
   - **关联 Issue**：如果有关联的 Issue，使用 `Closes #123` 或 `Fixes #123`。

5. **创建 Pull Request**  
   确认信息无误后，点击 **Create pull request** 按钮。

6. **等待审核**  
   - 仓库维护者会审核你的代码，可能会提出修改建议。
   - 如果收到反馈，请在本地分支修改后再次 `push`，PR 会自动更新。
   - 审核通过后，你的代码将被合并到原仓库。

### 同步上游更新（可选但推荐）

在你提交 PR 前后，原仓库可能有新的提交。保持你的分支与上游同步可以避免合并冲突：

```bash
# 获取上游最新代码
git fetch upstream

# 切换到 main 分支
git checkout main

# 合并上游的 main 分支
git merge upstream/main

# 推送到你的 Fork
git push origin main

# 切回你的功能分支
git checkout <你的分支名>

# 将上游的 main 合并到你的功能分支
git merge main
```

---

## 5. 常见问题

### Q: Push 时提示权限被拒绝？
**A:** 请确认你使用的是你自己的 Fork 地址（`git@github.com:<你的用户名>/...`），而非原仓库地址。如果使用 HTTPS，可能需要[配置 Personal Access Token](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/managing-your-personal-access-tokens)。

### Q: 如何处理合并冲突？
**A:** 
1. 按照上方「同步上游更新」的步骤拉取最新代码
2. 执行 `git merge main` 时会提示冲突文件
3. 手动编辑冲突文件，保留需要的代码，删除冲突标记（`<<<<<<<`、`=======`、`>>>>>>>`）
4. 保存后执行 `git add <文件名>` → `git commit` 完成合并

### Q: PR 被要求修改怎么办？
**A:** 直接在同一个功能分支上修改代码，提交并推送即可。PR 会自动更新，无需重新发起。

### Q: 提交信息应该怎么写？
**A:** 推荐使用[约定式提交（Conventional Commits）](https://www.conventionalcommits.org/zh-hans/)格式：
- `feat: 实现 PID 输出限幅功能`
- `fix: 修复积分饱和问题`
- `docs: 更新 README 文档`
- `refactor: 重构 update 函数结构`

---

## 项目结构速查

```
try_to_impl_pid/
├── src/
│   ├── pid.hpp              # PID 控制器头文件
│   ├── pid.cpp              # 👈 你需要实现 update 函数
│   ├── main.cpp             # 👈 你需要调优 cfg 参数
│   └── test.hpp             # PID 测试工具（头文件，inline 函数）
├── pid_testing_and_visualization/
│   └── pid_test_utils.hpp   # 可视化工具头文件（子模块）
├── .vscode/
│   └── tasks.json           # VSCode 构建任务配置
├── README.md
└── CONTRIBUTING.md
```

---

如有任何问题，欢迎在 [Issues](https://github.com/vex-crepe/try_to_impl_pid/issues) 中提出！感谢你的贡献 🎉
