local present, null_ls = pcall(require, "null-ls")

if not present then
   return
end

null_ls.setup({
    sources = {
        null_ls.builtins.formatting.clang_format,
    },
})
