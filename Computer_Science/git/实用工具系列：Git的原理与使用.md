# 实用工具系列：Git的原理与使用

## 前言

​	笔者最近的工作已经有所着落，现在打算准备更新一点实用工具系列来加强一下对Git的原理和使用上的理解。虽然说一个广泛流行的观点是——会用就行。但是笔者用了三年的Git，还真发现会用就行在这里不咋管用。所以，颠覆我之前的习惯——优先说咋用；我决定先从原理上入手。

## 为什么是工作区，暂存区，本地仓库

​	咱们写过Paper的都知道，改稿好几次备份好几次防止别人来一句：“欸还是你XXX月XXX日的那个好用，恢复回来吧。”。Git就是这个作用。它是一个版本管理控制系统。专门用来逐步登记一个工程中每一个阶段的开发。

​	早期程序员经过这样的思考：我们的工作需要在本地的一个目录执行（这就是工作区 / 工作目录（working directory）），然后上传到一个暂存区展示保留后（暂存区 / 索引（staging area / index）），准备提交到自己的一个本地仓库（我们和其他人协作的成果放在了这里）。这就是我们他讨论的三个区域。

在常见的工作流里，Git 的基本过程通常被描述为三步：

1. 在 **工作区（working directory）** 编辑文件（也叫工作树）。
2. 用 `git add` 把修改**放到暂存区（staging area / index）**，也就是告诉 Git “下一次提交我要包含这些内容”。
3. 用 `git commit` 把暂存区的内容写入 **本地仓库（.git/objects）**，形成一个不可变的 commit 对象。

这是 Git 的典型高层流程：工作区 → 暂存区 → 本地仓库（最终变成 commit）。可以参考 Pro Git（看这本书学Git有点大炮打蚊子，但是值得懂了之后一看）。

> Fast Reference: [Git](https://git-scm.com/book/en/v2/Getting-Started-What-is-Git%3F)

回到正题，这就是下面三个工作区的定义

#### 工作区（Working Directory / Working Tree）

工作区就是你在磁盘上看到并编辑的那些文件夹和文件；它反映了你当前检出（checkout）某个 commit 的那棵树（tree），但可以包含未暂存的修改或未跟踪的新文件。

#### 暂存区（Staging Area / Index）

暂存区（index）是 Git 的一个关键且常被误解的概念：它不是内存中的临时结构，而是一个位于 `.git` 下的持久化文件（称为 index 文件），用于记录“将要提交”的目录树条目（包括文件名、blob id、文件模式、时间戳等）。暂存区允许你**选择性地**提交变更（例如只提交部分文件或部分文件的改动），这也是 Git 相比不少集中式版本控制系统的一大优势。有关 staging/index 的权威解释请见官方文档。

#### 本地仓库（.git，object database）

本地仓库核心是一个**内容寻址（content-addressable）**的对象数据库：所有数据都以对象的形式保存在 `.git/objects`（或打包进 packfile），对象通过哈希值（历史上为 SHA-1，Git 已引入对 SHA-256 的可选支持）来唯一标识。Git 的对象主要有四种类型：**blob（文件内容）**、**tree（目录/索引映射）**、**commit（提交，包含元信息和指向一个 tree）**、**tag（注释标签）**。每次提交会生成一个新的 commit 对象，commit 指向一个 tree，而 tree 又引用 blob 或子 tree，从而把项目快照连接成一个有向无环图（DAG）。关于对象模型的细节可参考《Pro Git》的 internals 章节。

## 说一说几个经典的命令

#### `git add <file>`

高层：把工作区的改动记录到暂存区（index），为下一次 `git commit` 准备内容。
 底层（隐含步骤）：

1. Git 对该文件的内容做哈希（`git hash-object -w <file>` 相当于把该内容写成 blob 并返回其对象 id），把内容作为一个 `blob` 对象保存在对象数据库（初期为 loose object）。
2. Git 更新 index，把这个路径与对应的 blob id、模式信息写入 index 文件（即暂存区）。

注意：`git add` 并不是直接“把修改写进 commit”，它只把文件快照写到对象数据库并把索引指向那个 blob，真正的快照组合在 `git commit` 时形成 tree。关于 staging 的官方说明可以参考。

#### `git commit`

高层：把暂存区的当前内容写成一个 commit（包含作者、时间、父提交、commit message），并把当前分支（比如 `refs/heads/main`）更新为指向这个新 commit，HEAD 也随之指向它。
 底层（简化顺序）：

1. 读 index，基于 index 的条目构建一棵 tree（可以用 `git write-tree` 查看或生成该 tree），tree 引用了之前 `git add` 创建的 blob。
2. 创建一个 commit 对象（`git commit-tree`），把这次提交的元信息以及指向该 tree 的引用写入对象数据库，得到一个 commit id（哈希值）。
3. 更新引用（refs）：把当前分支的引用移动到这个新 commit（`git update-ref`）。
    这些“低级 plumbing 命令”确实存在并且可以串联使用，Git 的“porcelain”（高层命令）例如 `git commit`、`git add` 等只是把这些 plumbing 调用封装、对用户做友好交互。关于 plumbing vs porcelain 的讨论见官方章节。

下面是一个把上述流程以命令链“手工重演”的示例（只做示范，不是日常工作流必需）：

```bash
# 1) 把文件内容写成 blob（返回哈希）
git hash-object -w README.md
# 2) 把文件写进 index（可用 update-index）
git add README.md   # 高层方式
# 或者更显式地：
git update-index --add --cacheinfo 100644,<blobid>,README.md

# 3) 根据 index 写 tree
git write-tree   # 返回 treeid

# 4) 用 tree 创建 commit（需要父 commit id 和 message）
echo "Initial commit" | git commit-tree <treeid> -p <parent> 

# 5) 更新分支引用
git update-ref refs/heads/mybranch <newcommitid>
```

------

#### 对象存储的两种形态：散对象（loose）与 packfile

当你频繁修改并提交时，`.git/objects` 里会有大量以哈希命名的文件（称为 loose objects）。为了节省空间与提高传输效率，Git 提供 **packfile**：把很多对象打包、对类似对象做 delta 压缩，并生成一个索引文件 `.idx` 以便快速查找。Git 的垃圾回收与打包机制（`git gc`，`git repack`）会把松散对象合并成 packfile，这对大仓库和网络传输尤其重要。官方对 packfile 的行为和格式有详细说明。

------

#### 引用（refs）、分支（branches）、HEAD 与历史的表示

- **refs**（引用）是对 commit 的命名指针，常见位置包括 `refs/heads/`（本地分支）、`refs/remotes/`（远程分支）和 `refs/tags/`（标签）。
- **HEAD** 通常是一个符号引用，指向当前检出的分支（例如 `refs/heads/main`），也可以直接指向某个 commit（处于“detached HEAD”状态）。
- Git 的历史是一个由 commit（节点）通过父指针连接成的 DAG（有向无环图），分支仅仅是指向某个 commit 的指针；创建新 commit 本质上是把分支指向移动到新节点，从而“记录历史”。 这些概念同样在 Pro Git 书中有清晰描述。

------

#### 远端交互的核心：协商 + pack 传输

当你 `git fetch`、`git push` 时，Git 会进行“协商（negotiation）”来决定双方谁已经拥有哪些对象，只传输需要的对象，并且通常以 packfile 形式发送以减少体积。简单地说，推送/拉取不是把完整仓库拷贝过去，而是智能地比较引用并通过差异打包传输对象，从而高效同步。packfile 在这里发挥了决定性作用——既减少了磁盘占用，也减少了网络流量。官方 internals 对此有说明。

------

## 几个Ideas And Suggestions

理解内部实现后，下面的日常建议会更有说服力：

- **小而原子（atomic）的提交**：一次 commit 只做一件事（bug 修复或一个功能），因为 commit 是不可变且可被引用的快照。
- **用暂存区做选择性提交**：当你修改多个不相关文件时，用 `git add -p` 或选择性 add 来把相关改动放进一个 commit。
- **避免在公共分支上强推（force push）**：重写公共历史会影响协作人员的 refs，除非确认所有人都知情。
- **定期 `git gc` 并关注仓库体积**：在大仓库或长期开发中，packfile 与垃圾回收能显著节省磁盘与网络成本。
- **注意哈希算法兼容性**：不要在没有充分验证工具链（CI、托管服务、镜像工具）支持的情况下随意切换成 SHA-256 仓库。

## 几个常见的命令和说明

| 分类           | 命令                                             | 作用                   | 说明                              |
| -------------- | ------------------------------------------------ | ---------------------- | --------------------------------- |
| **配置**       | `git config --global user.name "xxx"`            | 设置用户名             | 在全局配置中写入用户名            |
|                | `git config --global user.email "xxx@email.com"` | 设置邮箱               | 在全局配置中写入邮箱              |
|                | `git config --list`                              | 查看配置信息           | 包括用户名、邮箱、别名等          |
| **仓库操作**   | `git init`                                       | 初始化仓库             | 在当前目录创建 `.git` 目录        |
|                | `git clone <url>`                                | 克隆远程仓库           | 支持 `ssh` / `https`              |
| **状态与查看** | `git status`                                     | 查看工作区/暂存区状态  | 哪些文件被修改、跟踪或未跟踪      |
|                | `git log`                                        | 查看提交历史           | 支持 `--oneline`、`--graph`       |
|                | `git reflog`                                     | 查看 HEAD 引用历史     | 可以找回丢失的提交                |
|                | `git diff`                                       | 查看文件改动           | 比较工作区/暂存区/版本库差异      |
|                | `git show <commit>`                              | 显示某次提交详细信息   | 包括变更内容、提交者等            |
| **文件操作**   | `git add <file>`                                 | 添加到暂存区           | 可以用 `.` 表示全部               |
|                | `git rm <file>`                                  | 删除文件并记录到暂存区 |                                   |
|                | `git mv <old> <new>`                             | 文件改名               | 相当于 `mv` + `git add`           |
| **提交**       | `git commit -m "msg"`                            | 提交暂存区             | 用于保存历史                      |
|                | `git commit --amend`                             | 修改上一次提交         | 可以改 message 或补充文件         |
| **分支操作**   | `git branch`                                     | 列出分支               | `*` 标记当前分支                  |
|                | `git branch <name>`                              | 新建分支               |                                   |
|                | `git branch -d <name>`                           | 删除分支               | `-D` 强制删除                     |
|                | `git checkout <branch>`                          | 切换分支               |                                   |
|                | `git checkout -b <branch>`                       | 新建并切换分支         |                                   |
|                | `git switch <branch>`                            | 切换分支（新写法）     |                                   |
|                | `git switch -c <branch>`                         | 新建并切换分支         |                                   |
| **合并与变基** | `git merge <branch>`                             | 合并分支               | 默认 fast-forward 或 merge commit |
|                | `git rebase <branch>`                            | 变基                   | 将提交迁移到目标分支之上          |
|                | `git rebase -i <commit>`                         | 交互式变基             | 修改、压缩、删除历史提交          |
| **远程操作**   | `git remote -v`                                  | 查看远程仓库           |                                   |
|                | `git remote add origin <url>`                    | 添加远程仓库           |                                   |
|                | `git fetch`                                      | 获取远程更新           | 只下载，不合并                    |
|                | `git pull`                                       | 拉取并合并             | 相当于 `fetch` + `merge`          |
|                | `git push`                                       | 推送本地提交           | 上传到远程仓库                    |
|                | `git push -u origin <branch>`                    | 设置默认推送分支       | 之后直接 `git push` 即可          |
| **标签**       | `git tag`                                        | 查看标签               |                                   |
|                | `git tag <name>`                                 | 创建轻量标签           |                                   |
|                | `git tag -a <name> -m "msg"`                     | 创建附注标签           | 包含更多信息                      |
|                | `git push origin <tag>`                          | 推送标签               |                                   |
| **撤销与恢复** | `git checkout -- <file>`                         | 丢弃工作区改动         |                                   |
|                | `git reset [--soft                               | --mixed                | --hard] `                         |
|                | `git revert <commit>`                            | 撤销某次提交           | 会产生一个反向提交                |
|                | `git restore <file>`                             | 恢复文件（新写法）     | 类似 `checkout --`                |
| **临时存储**   | `git stash`                                      | 暂存工作进度           | 清空工作区                        |
|                | `git stash list`                                 | 查看 stash 列表        |                                   |
|                | `git stash pop`                                  | 恢复并删除 stash       |                                   |
|                | `git stash apply`                                | 恢复但保留 stash       |                                   |
| **清理**       | `git clean -f`                                   | 删除未跟踪文件         | 强制执行                          |
|                | `git clean -fd`                                  | 删除未跟踪文件和目录   |                                   |

------

## `git reset`、`git revert`、`git rebase` 的区别与原理

### 1. `git reset`

- **作用**：重置当前分支的 `HEAD` 到指定提交。
- **模式**：
  - `--soft`：仅移动 HEAD，不改暂存区和工作区（文件保持不动）。
  - `--mixed`（默认）：移动 HEAD，清空暂存区，保留工作区改动。
  - `--hard`：移动 HEAD，同时清空暂存区和工作区（⚠️ 危险）。
- **原理**：直接改变分支指针，属于“改写历史”，不适合已推送分支。

------

### 2. `git revert`

- **作用**：撤销某次提交，但**不会删除提交历史**，而是创建一个“反向提交”。
- **原理**：保留历史，增加新的 commit，用来抵消之前的修改。
- **安全性**：适合公共分支（因为不会改写历史）。

------

### 3. `git rebase`

- **作用**：把当前分支的提交“搬到”另一个分支最新提交之上，形成线性历史。
- **原理**：逐个提交“复制”到新的 base 上，生成新的 commit ID。
- **好处**：历史干净，没有多余的 merge commit。
- **风险**：改写提交历史，不要在公共分支使用。

