return {
     {"nvim-treesitter/nvim-treesitter",
	build = ":TSUpdate",
	config = function()
		local config = require("nvim-treesitter.configs")
		config.setup({
		auto_install = true,
   		ensure_installed = {"cpp", "c", "javascript"},
   		highlight = {enable = true},
   		indent = {enable = true},
		})	
	end
     },
}
