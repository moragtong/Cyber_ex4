start_of_page = """<!DOCTYPE html> <html>
                    <head>
                    </head>
                    <body>
                        Hello"""
end_of_page = """ </body> </html>"""
script_size = len(start_of_page) + len(end_of_page)
print(f"Content-Length: {script_size}")
print(150 * "a")
