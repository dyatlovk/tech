local projectDir = vim.fn.getcwd()

-- load settings after client attached
local lsp_present = pcall(require, "lspconfig")
if lsp_present then
  vim.cmd('luafile ' .. projectDir .. "/.nvim/lsp.lua")
  vim.cmd('luafile ' .. projectDir .. "/.nvim/dap.lua")
  vim.cmd('luafile ' .. projectDir .. "/.nvim/null_ls.lua")
  vim.cmd('luafile ' .. projectDir .. "/.nvim/keymaps.lua")
end

local notify = vim.notify
-- vim.notify = function(msg, ...)
--     if msg:match("warning: multiple different client offset_encodings") then
--         return
--     end
--
--     notify(msg, ...)
-- end

