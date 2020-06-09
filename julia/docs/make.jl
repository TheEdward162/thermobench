using Documenter
using Thermobench

DocMeta.setdocmeta!(Thermobench,
                    :DocTestSetup, :(using Thermobench, DataFrames),
                    recursive=true)

using DataFrames

makedocs(
    sitename = "Thermobench",
    format = Documenter.HTML(),
    modules = [Thermobench],
    doctest = false,
    workdir = @__DIR__,
)

# using DocumenterMarkdown
# makedocs(
#     sitename = "Thermobench",
#     format = DocumenterMarkdown.Markdown(),
#     build = "build-markdown",
#     modules = [Thermobench]
# )

# Documenter can also automatically deploy documentation to gh-pages.
# See "Hosting Documentation" and deploydocs() in the Documenter manual
# for more information.
deploydocs(
    repo = "github.com/CTU-IIG/thermobench.git"
)
