require(ggplot2)

# Read the statistics
data <- read.table("../output/performance.txt", sep = " ", header = TRUE)

# Prepare the output - Use the standard A4 size (in inches)
pdf(file = "../output/graph.pdf", width = 11.69, height = 8.27)
# Plot the ratio for all n, with a red line defining what the bound should be below
ggplot(data, aes(n, Time/n)) + 
  geom_point() +
  ylab("Time (sec) / n") +
  scale_x_continuous(name="n", breaks=2^seq(2, nrow(data)+1, 2), trans = "log2")
# Close PDF file
garbage <- dev.off()