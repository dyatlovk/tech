-- lsp
vim.api.nvim_set_keymap('n', "<leader>ff", ":Lspsaga lsp_finder<CR>", {desc = "Lspsaga: Finder"});
vim.api.nvim_set_keymap('n', "<leader>fc", ":Lspsaga code_action<CR>", {desc = "Lspsaga: Code Action"});
vim.api.nvim_set_keymap('n', "<leader>fr", ":Lspsaga rename<CR>", {desc = "Lspsaga: Rename"});
vim.api.nvim_set_keymap('n', "<C-]>", ":lua vim.lsp.buf.definition()<CR>", {desc = "LSP: definition"});
vim.api.nvim_set_keymap('n', "<leader>fo", ":Lspsaga outline<CR>", {desc = "LSP: outline"});
vim.api.nvim_set_keymap("n", "<F12>", ":ClangdSwitchSourceHeader<CR>", { desc = "Switch Source/Header" })

vim.api.nvim_set_keymap('n', "<F3>", ":lua require('nvterm.terminal').send('make test', 'vertical')<CR>", {desc = "Make: test"});
vim.api.nvim_set_keymap('n', "<F2>", ":lua require('nvterm.terminal').send('make rebuild', 'vertical')<CR>", {desc = "Make: rebuild"});
