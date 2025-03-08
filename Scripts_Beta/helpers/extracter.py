# Define the file path
file_path = 'Scripts_Beta/helpers/data.txt'  # Replace with your file's path

# Initialize an empty set to store unique values
unique_entries = set()

# Open the file and read it line by line
with open(file_path, 'r') as file:
    for line in file:
        # Strip leading/trailing whitespace
        line = line.strip()
        
        # Find the part after the first '}' and add it to the set
        if '}' in line:
            part = line.split('}', 1)[1].strip()  # Extract part after '}' and strip extra spaces
            unique_entries.add(part)

# Output the unique entries
for entry in unique_entries:
    print(entry)
