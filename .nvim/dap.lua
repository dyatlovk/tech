local dap_present, dap = pcall(require, "dap")

if not dap_present then
  return
end

local M = {}

M.debugAdapterSetup = function()
  dap.adapters.lldb = {
    type = 'executable',
    command = '/usr/bin/lldb-vscode', -- adjust as needed, must be absolute path
    name = 'lldb'
  }
end

M.debugCppConfig = function ()
  dap.configurations.cpp = {
    {
      name = 'Launch',
      type = 'lldb',
      request = 'launch',
      program = '~/Games/tech2/bin/game',
      cwd = '${workspaceFolder}',
      stopOnEntry = false,
      args = {},
    },
  }
  dap.configurations.c = dap.configurations.cpp
end

M.debugAdapterSetup()
M.debugCppConfig()

return M
