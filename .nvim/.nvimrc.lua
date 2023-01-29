local projectDir = vim.fn.getcwd()

-- load settings after client attached
local lsp_present = pcall(require, "lspconfig")
if lsp_present then
  vim.cmd('luafile ' .. projectDir .. "/.nvim/lsp.lua")
  vim.cmd('luafile ' .. projectDir .. "/.nvim/dap.lua")
  vim.cmd('luafile ' .. projectDir .. "/.nvim/null_ls.lua")
end

vim.api.nvim_set_keymap('n', "<F2>", ":make rebuild<CR>", {desc = "Make: rebuild"});
vim.api.nvim_set_keymap('n', "<F3>", ":make test<CR>", {desc = "Make: test"});

local notify = vim.notify
-- vim.notify = function(msg, ...)
--     if msg:match("warning: multiple different client offset_encodings") then
--         return
--     end
--
--     notify(msg, ...)
-- end

