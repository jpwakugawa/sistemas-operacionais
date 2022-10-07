array = {}

for i=1,5 do
	array[i] = {}

	for j=1,5 do
		array[i][j] = math.random(10)
	end
end

function printArray()
	for i=1,5 do
		for j=1,5 do
			result = array[i][j]
			print(result)
		end
	end
end

printArray()
