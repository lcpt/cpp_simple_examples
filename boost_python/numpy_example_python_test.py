import numpy as np
import numpy_example
x = np.array([1, 2, 3, 4, 5])
sum, count = numpy_example.count_and_sum(x.astype(np.double))
print(f"Sum is {sum} from {count} elements")
