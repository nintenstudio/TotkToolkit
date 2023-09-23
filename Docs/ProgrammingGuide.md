## How are the files organized?
### Concepts
There are several key concepts to how this project is set up. Here's a list of what we'll discuss:
* Public and private separation
* Namespace and file structure equality
* Parent/child class file structure
* Nested filetrees

#### Public and Private Separation
The concept of "public" and "private" classes, functions, and data is not a new one. But to catch you up if you're unaware, the idea is that some stuff should be exposed to dependants, while other stuff is internal and should not be exposed. While nothing currently depends on TotkToolkit as a library, I am keeping this Public/Private structure in case something at one point does. It is also important for libraries such as Formats. Public files are organized under a `Public` directory, whilst private files are under a `Private` directory. I hope that makes sense!

#### Namespace and File Structure Equality
For organizational purposes, all namespaces match the folders the file is in, and vice versa. This can result in very long namespaces, however I don't consider that a problem. With modern monitor widths, I find it more important to carry that information than to have a compact line of code.

#### Parent/Child Class File Structure
This one's super simple! In simple cases where you need a parent class and several child classes that extend only from it, this pattern often applies. The idea is that the parent class file should be located next to a folder containing the children class files. An example is `UI/Window.h` and `UI/Windows/`.
There are more complicated examples that do not fully follow this idea, such as `Messaging/Receiver.h` and `Messaging/ExternalReceivers/`, but for simple cases it's a pattern to follow.


#### Nested Filetrees
This one's a little bit hard to explain, so I'll give an example:
The file `UI/EditorSystem.h` exists. So too does `Messaging/ExternalReceivers/UI/EditorSystem.h`. It's not that these files share the same function, but they are related. (In this case, one is an external receiver for another.) The idea is that the project file structure is mirrored in the directory `Messaging/ExternalReceivers` so that we can be specific about what functionality is being extended.

## How should I program?
### Concepts
I don't nitpick too much in the way of what your code looks like. But there are a few things that should be kept in mind:
* Memory management
* Primitive aliases

#### Memory Management
There are often only two types of data when it comes to memory: data that is owned by a specific object and data that floats between objects. Keep in mind that I will often count data in the second category even if it is not shared between multiple objects, simply because it *could* be. Especially so if it is publicly accessable.

Data that is shared between objects should in most cases be wrapped in an `std::shared_ptr`. This ensures that memory management is taken care of automatically. Data that is associated with a class and could be considered as part of that class can be expressed as a basic pointer type. (Though sometimes it makes sense to use a `std::shared_ptr` anyway.)

#### Primitive Aliases
This is super minor, and at times I forget to adhere to it. But when I remember to, I use the primitive aliases located in `Lib/Formats/Aliases/Primitives.h`. This is to introduce a logical naming scheme to primitives, since in C++ that doesn't really exist by default.