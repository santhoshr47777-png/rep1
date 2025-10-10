from reportlab.lib.pagesizes import A4
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, Table, TableStyle
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib import colors

# Define the PDF file path (Windows)
pdf_path = r"C:\Users\santh\OneDrive\Desktop\college admission\sanjeeth.pdf"

# Create the PDF document
doc = SimpleDocTemplate(pdf_path, pagesize=A4)
styles = getSampleStyleSheet()

# Custom styles
style_title = ParagraphStyle('title', parent=styles['Heading1'], alignment=1, textColor=colors.HexColor("#1F4E79"))
style_section = ParagraphStyle('section', parent=styles['Heading2'], textColor=colors.HexColor("#1F4E79"), spaceBefore=12)
style_body = styles['Normal']
style_center = ParagraphStyle('center', parent=styles['Normal'], alignment=1)

# Resume content
content = []

# Header
content.append(Paragraph("<b>SANJEETH N</b>", style_title))
content.append(Paragraph("Email : sanjeethnagaraj@gmail.com", style_section))
content.append(Paragraph("phone : 8807859724", style_section))
content.append(Paragraph("Address : 2/211 THILAGAR STREET, M.A.NAGAR, PADIANALLUR, REDHILLS, CHENNAI 52", style_section))
content.append(Spacer(1, 12))

# Education Section
content.append(Paragraph("Education", style_section))
edu_data = [
    ["Qualification", "School", "Year", "Percentage"],
    ["HSC", "ELITE MATRIC HR. SEC. SCHOOL", "2023", "90.1%"],
    ["SSLC", "ELITE MATRIC HR. SEC. SCHOOL", "2021", "86.3%"]
]
table = Table(edu_data, colWidths=[80, 250, 50, 50])
table.setStyle(TableStyle([
    ('BACKGROUND', (0,0), (-1,0), colors.HexColor("#1F4E79")),
    ('TEXTCOLOR', (0,0), (-1,0), colors.white),
    ('ALIGN',(0,0),(-1,-1),'CENTER'),
    ('GRID', (0,0), (-1,-1), 0.5, colors.black),
    ('FONTNAME', (0,0), (-1,0), 'Helvetica-Bold')
]))
content.append(table)
content.append(Spacer(1, 12))

# Skills
content.append(Paragraph("Skills", style_section))
skills = ["C++", "Python"]
for skill in skills:
    content.append(Paragraph(f"• {skill}", style_body))
content.append(Spacer(1, 12))

# Languages
content.append(Paragraph("Languages", style_section))
languages = ["Tamil", "English"]
for lang in languages:
    content.append(Paragraph(f"• {lang}", style_body))
content.append(Spacer(1, 12))

# Extra-Curricular Activities
content.append(Paragraph("Extra-Curricular Activities", style_section))
activities = ["Member: Language Club"]
for act in activities:
    content.append(Paragraph(f"• {act}", style_body))
content.append(Spacer(1, 12))

# Academic Project
content.append(Paragraph("Academic Project", style_section))
content.append(Paragraph("<b>BLOOD DONATION SYSTEM</b>", style_body))
content.append(Paragraph("Developed software to automate the blood donation process.", style_body))
content.append(Paragraph("Features include donation applications, document verification.", style_body))
content.append(Spacer(1, 12))

# Personal Details
content.append(Paragraph("Personal Details", style_section))
content.append(Paragraph("Date of Birth: 24/07/2008", style_body))
content.append(Paragraph("Hobbies: Reading, Sports", style_body))

# Build PDF
doc.build(content)

print(f"PDF resume generated at: {pdf_path}")
