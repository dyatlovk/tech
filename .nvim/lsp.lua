local present, lsp = pcall(require, "lspconfig")
if not present then
  return
end

local clangd_ext = require("clangd_extensions")
local util = require 'vim.lsp.util'
local capabilities = require("plugins.configs.lspconfig").capabilities

local formatting_callback = function(client, bufnr)
  vim.keymap.set('n', '<leader>fm', function()
    local params = util.make_formatting_params({})
    client.request('textDocument/formatting', params, nil, bufnr)
  end, { buffer = bufnr, desc = "Format" })
  -- clangd_ext.setup() -- warnings
end

local on_attach = function(client, bufnr)
  if client.name ~= 'ccls' then
    formatting_callback(client, bufnr)
  end
end

lsp['clangd'].setup{
  on_attach = function(client, bufnr)
    on_attach(client, bufnr)
  end,
  cmd = {
     "clangd",
  },
  capabilities = capabilities,
}
