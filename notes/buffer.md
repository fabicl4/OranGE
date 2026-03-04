# OpenGL Buffer

Los ResourceManagers no pueden incluir operaciones que alterasen la 

Tipos principales de Buffers de OpenGL (*Buffer Binding Target*):

- Vertex Buffer (VBO)
- Index Buffer (IBO)
- Uniform Buffer (UBO)
- Shader Storage Buffer (SSBO)

Otros tipos de buffers que en este momento no voy a utilizar:

- GL_COPY_READ_BUFFER
- GL_COPY_WRITE_BUFFER
- GL_PIXEL_PACK_BUFFER
- GL_PIXEL_UNPACK_BUFFER
- GL_DRAW_INDIRECT_BUFFER
- GL_DISPATCH_INDIRECT_BUFFER
- GL_ATOMIC_COUNTER_BUFFER
- GL_TRANSFORM_FEEDBACK_BUFFER
- GL_TEXTURE_BUFFER

El buffer según(*BufferUsage*) sus usos pueden ser:  

GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.

